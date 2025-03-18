 // Si se compila con Arduino 1.8.5 no da problemas en Linkado.
// pero antes de que se actualizaran las placas. 

// En la 1.8.9 va pero evitar que se actualice.
//
//
// #define SW_VERSION "1.9" con cambio para placa verde y negra.
// Cambios metidos por Prof. Andrés Roldán
// En Config.h se mete esto para cambiar rápido de versión.
//    #define PCB_VERSION_21  //PCB verde donde los OUT1 y 2 se usan los pines del serial TX/RX0
//      #define PCB_VERSION_22  //PCB negra bien con 7805
// 
// Fecha:  26/08/2019



#include "config.h"

#include "pwm_gen.h"
#include "virtual_PWM.h"
#include "lifo_mem.h"
#include "lcd_menu.h"
#include "IO_control.h"
#include "uart_control.h"

pwm_pin_TD pwms[PWM_PINS];
lifo_mem event_q;
char rx_buf[20];
char rotary_buf[20];
uint8_t rx_buf_counter=0;
uint32_t last_rotary_event = 0;
uint8_t last_rotary_event_dir=0;
uint32_t last_button_push =0;
uint32_t seconds_passed_since_ui=0;
pwm_to_eeprom_t aux2[8];

void setup(){
    int i;
    pwm_to_eeprom_t aux[8];

    // Serial.println(aux[1].nombre);

    lcd_menu_init(pwms);
    setup_pwm_interrupt();
    initialize_all_pins(pwms);

    // Inicializamos el vector de PWM_to_EEPROM la posición 0 de las 4 que
    // tenemos en la EEPROM. Si esta virgen la inicializamos.
    eeprom_init(aux, 0);

    for (i = 0; i < 8; i++){
        configure_pwm_pin(pwms, i, aux[i].freq, aux[i].dty);
        pwm_pin_enable(pwms, i, aux[i].en);
    }

    setup_IO_interrupts();
    uart_init();

    #ifdef DEBUG_ROTARY
        Serial.begin(9600);
        Serial.println(F("Debuging Serial data for the LCD and Rotaty"));
    #endif
};

void loop(){
    event_td data;
    uint32_t second = millis();
    unt8_t screensaver_is_on = 0;

    while(1) {
        delay(1); // Dont know why, it just doesn work without this

        if (lifo_pop(&event_q, &data)){
            process_event(data, rx_buf, pwms);
        }

        if (millis() - second > 1000){
            second = millis();
            seconds_passed_since_ui++;
        }

        if ((seconds_passed_since_ui == 0) && screensaver_is_on){
            screensaver_is_on = 0;
            lcd_reload_screen();
        }

        if ((seconds_passed_since_ui >= SCREENSAVER_TIMEOUT) &&
            !screensaver_is_on){
            lcd_screensaver();
            screensaver_is_on=1;
        }

        char command = uart_getc();

        if (command == 'C'){
            lcd_clrscr();
            lcd_gotoxy(0, 0);
            lcd_puts_P(" Enviando datos"); 
            
            pwm_to_eeprom_t pwm[8];

            // Leer los valores almacenados en la memoria EEPROM
            eeprom_load_pwms(pwm,0);

            // Enviar los valores al host a traves del puerto serial
            uart_puts(pwm[0].freq);

            uart_puts(",");
            uart_puts(pwm[0].dty);

            uart_puts(",");
            uart_puts(pwm[0].en);

            uart_puts(",");
            uart_puts(pwm[0].phs);

            uart_puts(",");
            uart_puts(pwm[0].nombre);
        
            command = 0; // Para que no entre en bucle
        }
    }
}


void process_rotary_int(){
    seconds_passed_since_ui = 0;
    event_td encoder_event;
    uint8_t ro = process_rotary();

    if (ro == DIR_CW){ // UP
        encoder_event.event_enum = MOVEMENT_UP;
        encoder_event.parameter2 = ROTARY_SLOW;
        lifo_push(&event_q, encoder_event);

        last_rotary_event_dir = MOVEMENT_UP;
        last_rotary_event = millis();
    }

    else if (ro == DIR_CCW){ // DOWN
        encoder_event.event_enum = MOVEMENT_DOWN;
        encoder_event.parameter2 = ROTARY_SLOW;

        lifo_push(&event_q, encoder_event);

        last_rotary_event_dir = MOVEMENT_DOWN;
        last_rotary_event = millis();
    }
}


ISR(TIMER2_COMPA_vect){
    #ifdef DEBUG_INTERRUPT_USAGE
        DEBUG_INTERRUPT_PORT |= _BV(DEBUG_INTERRUPT_PIN);
    #endif

    pwm_cycle(pwms);

    #ifdef DEBUG_INTERRUPT_USAGE
        DEBUG_INTERRUPT_PORT &= ~(_BV(DEBUG_INTERRUPT_PIN));
    #endif
}

/*  INTERRUPT PINs in ATMega2560

    INT0, 1, 2, 3 are physical pins 43,44,45,46 on the ATMega2560, D21,20,19,18
    on the Mega2560 schematic.

    INT4, 5, 6, 7 are physical pins 6, 7, 8, 9 on the ATMega2560, D2, D3 and
    not connected, not connected on the Mega2560 schematic. Loss of 2
    interrupts there.

    button interrupt -> EXT2
*/

ISR(INT2_vect){
    seconds_passed_since_ui = 0;
    event_td encoder_event;

    if (millis() - last_button_push > BUTTON_DEBOUNCING){
        encoder_event.event_enum = BUTTON_PUSH;
        lifo_push(&event_q, encoder_event);
        last_button_push = millis();
    }
}

// Rotary interrupts
ISR(INT1_vect){
    process_rotary_int();
}

ISR(INT3_vect){
    process_rotary_int();
}

ISR (USART0_RX_vect){
    event_td uart_event;

    uint8_t c = read_uart_rx();
    if(c != '\r'){
        if(c == '\n'){
            rx_buf[rx_buf_counter] = '\0';
            rx_buf_counter = 0;
            uart_event.event_enum = UART_RX;
            // uart_event.parameter = rx_buf;

            lifo_push(&event_q, uart_event);
        }

        if ( c == '\0'){
            lcd_clrscr();
            lcd_gotoxy(0, 0);
            lcd_puts_P(" Enviando datos"); 

            pwm_to_eeprom_t pwm[8];

            // Leer los valores almacenados en la memoria EEPROM
            eeprom_load_pwms(pwm,0);
      
            // Enviar los valores al host a través del puerto serial
            uart_puts(pwm[0].freq);

            /*
                uart_puts(",");
                uart_puts(pwm[0].dty);

                uart_puts(",");
                uart_puts(pwm[0].en);

                uart_puts(",");
                uart_puts(pwm[0].phs);
                uart_puts(",");
                uart_puts(pwm[0].nombre);
            */
        }

        else {
            rx_buf[rx_buf_counter] = c;
            rx_buf_counter++;
        }
    }
}

/*
ISR(USART0_RX_vect){
    event_td uart_event;
    uint8_t c = read_uart_rx();
    if(c != '\r'){
        if(c == '\n'){
            rx_buf[rx_buf_counter] = '\0';
            rx_buf_counter = 0;
            uart_event.event_enum = UART_RX;
            // uart_event.parameter = rx_buf;

            lifo_push(&event_q, uart_event);
        }

        else {
            rx_buf[rx_buf_counter] = c;
            rx_buf_counter++;
        }
    }
}
*/