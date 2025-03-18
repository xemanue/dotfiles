#include <stdio.h>  // Para declarar sprintf y evitar "Warning: implicit
                    // declaration of function 'sprintf'"
#include "IO_control.h"

#define R_CW_FINAL 0x02
#define R_CW_BEGIN 0x01
#define R_CCW_BEGIN 0x00
#define R_CCW_FINAL 0x03

uint8_t rotary_state = R_CW_BEGIN;

const unsigned char ttable[4][4] = {
    // R_CCW_BEGIN
    {R_CCW_BEGIN, R_CW_BEGIN, R_CCW_BEGIN, R_CCW_FINAL},
    // R_CW_BEGIN
    {R_CW_BEGIN, R_CW_BEGIN, R_CW_FINAL, R_CCW_BEGIN},
    // R_CW_FINAL
    {R_CCW_BEGIN, R_CW_BEGIN, R_CCW_BEGIN, R_CCW_BEGIN},
    // R_CCW_FINAL
    {R_CCW_BEGIN, R_CW_BEGIN, R_CCW_BEGIN, R_CCW_BEGIN},
};

void print_state(uint8_t state){
    char *str;
    switch (state) {
        case R_CW_BEGIN:
            str = "R_CW_BEGIN";
            break;
        case R_CW_FINAL:
            str = "R_CW_FINAL";
            break;
        case R_CCW_BEGIN:
            str = "R_CCW_BEGIN";
            break;
        case R_CCW_FINAL:
            str = "R_CCW_FINAL";
            break;
        default:
            str = "UND";
            break;
    }

    uart_puts(str);
    uart_puts("\r\n");
}

void process_event(event_td data, char *rx_buf, pwm_pin_TD *pwms){
    char answer_buf[20];
    switch(data.event_enum){
        case MOVEMENT_UP: 
            #ifdef DEBUG_EVENT_LOOP
                Serial.println("Calling down");
            #endif
            lcd_down(data.parameter2);
            break;
        case MOVEMENT_DOWN: 
            #ifdef DEBUG_EVENT_LOOP
                Serial.println("Calling up");
            #endif
            lcd_up(data.parameter2);
            break;
        case BUTTON_PUSH:
            #ifdef DEBUG_EVENT_LOOP
                Serial.println("Calling button");
            #endif
            lcd_button_press();
            break;
        case QUICK_BUTTON_PUSH:
            lcd_quick_button();
        case UART_RX:
            parse_serial(rx_buf, pwms, answer_buf);
            uart_puts(answer_buf);
            break;
    }
}

/**
 * @details Interrupt 1 (pin 20 on the arduino) will be used for the rotary
 * control, activated on both falling and rising edges.
 * Interrupt 2 (pin 19) is used to control the push-button, and is only
 * activated on the rising edge (when the button is released).
 * More information can be found in the <a href="http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-2549-8-bit-AVR-Microcontroller-ATmega640-1280-1281-2560-2561_datasheet.pdf#page=110">ATmega2560 datasheet</a>
 */
void setup_IO_interrupts(){
    cli();

    pinMode(20, INPUT);
    pinMode(18, INPUT);
    pinMode(19, INPUT);

    // Interrupt 1 on any edge, Interrupt 2 on rising edge
    EICRA = (1<<ISC10) | (1<<ISC21) | (1<<ISC20) | (1<<ISC31) | (1<<ISC30);
    EIMSK = (1<<INT1) | (1<<INT2) ; // Enables interrupts 1 and 2
    sei();
}

uint8_t process_rotary(){
    // https://www.microchip.com/webdoc/AVRLibcReferenceManual/FAQ_1faq_use_bv.html
    uint8_t a = (ENCODER_A_PIN & _BV(ENCODER_A_BIT)) || 0;
    uint8_t b = (ENCODER_B_PIN & _BV(ENCODER_B_BIT)) || 0; // _BV(3) => 1 << 3
                                                           //        => 0x08
    unsigned char pinstate = (a << 1) | (b);
    
    /*
        uart_puts("[");a
        uart_putc('0'+(rotary_state & 0xf));
        uart_puts("] ");
    */

    // Determine the new state from pins and state table.
    rotary_state = ttable[rotary_state & 0xf][pinstate];
    
    #ifdef DEBUG_ROTARY
        uart_putc(pinstate+'0');
        uart_puts("-> ");
        print_state(rotary_state);
        uart_puts("\r\n");
    #endif

    if (rotary_state == R_CCW_FINAL){
        // uart_puts("ROT CCW \r\n");
        return DIR_CCW;
    }

    if (rotary_state == R_CW_FINAL){
        // uart_puts("ROT CW \r\n");
        return DIR_CW;
    }

    return DIR_NONE;
}

char *num2str(char *buf, int num, int length){
    int i;
    for (i = 0; i < length; i++){
        buf[i] = num % 10 + '0';
        num = num / 10;
    }

    char aux;
    for(i = 0; i < length / 2; i++){
        aux = buf[i];
        buf[i] = buf[length - i - 1];
        buf[length - i - 1] = aux;
    }

    buf[length] = '\0';

    return buf;
}

char *parse_serial(char *rx_buf, pwm_pin_TD *pwms, char *answer_buf){
    uint8_t channel = 0;
    uint16_t dty = 0;
    uint32_t frq = 0;
    uint8_t en;
    uint8_t cnt = 0;
    pwm_to_eeprom_t aux[8];

    int i = 0;
    strcpy(answer_buf , "NOK\r\n");

    if (rx_buf[cnt] == 'C'){
        channel = rx_buf[1] - '0';

        if (rx_buf[2] != 'E') return answer_buf;
        
        en = rx_buf[3] - '0';
        
        if (rx_buf[4] != 'F') return answer_buf;
        
        frq = (rx_buf[5] - '0') * 1000 +
              (rx_buf[6] - '0') * 100 +
              (rx_buf[7] - '0') * 10 +
              (rx_buf[8] - '0');

        if (rx_buf[9] != 'D') return answer_buf
        
        dty = (rx_buf[10] - '0') * 100 +
              (rx_buf[11] - '0') * 10 +
              (rx_buf[12] - '0');

        configure_pwm_pin(pwms, channel , frq, dty);
        pwm_pin_enable(pwms, channel, en);
        strcpy(answer_buf , "OK\r\n");

        return answer_buf;
    }

    if (rx_buf[cnt] == 'G'){
        cnt++;
        channel = rx_buf[cnt] - '0'; 
        sprintf(answer_buf, "C%uE%uF%04uD%03u\r\n", channel,
                                                    pwms[channel].en,
                                                    pwms[channel].frq,
                                                    pwms[channel].dty);
    }

    if (rx_buf[cnt] == 'S'){
        for (i = 0; i < 8; i++){
            aux[i].freq = pwms[i].frq;
            aux[i].dty = pwms[i].dty;
            aux[i].en =pwms[i].en;
        }

        eeprom_save_pwms(aux, 0);
        strcpy(answer_buf, "OK");
    }

    return answer_buf;
}