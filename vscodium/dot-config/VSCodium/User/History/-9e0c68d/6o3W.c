/* Copyright (C) GranaSAT - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Luis Sanchez <luissanv@ugr.es>, August 2018
 */

#include "config.h"
#include "lcd_menu.h"
// #include "ford.c"
// #include <Arduino.h>

uint8_t current_screen;
list_menu_td list_screen;
pwm_menu_td pwm_screen;
game_td game_screen;
pass_menu_td pass_screen;
pwm_to_eeprom_t intercambio[8];
lenta_menu_td lenta_screen;

uint8_t eeprom_start_address = 0x01;
char nombreCoche[12];

static const PROGMEM unsigned char rightArrow[] = {
    0x00,
    0x08,
    0x0C,
    0x0E,
    0x0E,
    0x0C,
    0x08,
    0x00
};
static const PROGMEM unsigned char leftArrow[] = {
    0x00,
    0x02,
    0x06,
    0x0E,
    0x0E,
    0x06,
    0x02,
    0x00
};
static const PROGMEM unsigned char upArrow[] = {
    0x00,
    0x00,
    0x04,
    0x0E,
    0x1F,
    0x00,
    0x00,
    0x00
};
static const PROGMEM unsigned char downArrow[] = {
    0x00,
    0x00,
    0x00,
    0x1F,
    0x0E,
    0x04,
    0x00,
    0x00
};
static const PROGMEM unsigned char goodTick[] = {
    0b00000000,
    0b00000000,
    0b00000001,
    0b00010110,
    0b00011100,
    0b00001000,
    0b00000000,
    0b00000000
};
static const PROGMEM unsigned char rightArrow_und[] = {
    0x00,
    0x08,
    0x0C,
    0x0E,
    0x0E,
    0x0C,
    0x08,
    0xFF};
static const PROGMEM unsigned char leftArrow_und[] = {
    0x00,
    0x02,
    0x06,
    0x0E,
    0x0E,
    0x06,
    0x02,
    0xFF
};
static const PROGMEM unsigned char und[] = {
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0xFF};

#define RIGHT_ARROW 0
#define LEFT_ARROW 1
#define UP_ARROW 2
#define DOWN_ARROW 3
#define GOOD_TICK 4
#define RIGHT_ARROW_UND 5
#define LEFT_ARROW_UND 6
#define BLANK_UND 7

char *convNum2str(char *buf, int num, int length){
    int i;
    char aux;

    num = (num > 0) ? num : -1 * num;
    for (i = 0; i < length; i++){
        buf[i] = num % 10 + '0';
        num = num / 10;
    }

    for (i = 0; i < length / 2; i++){
        aux = buf[i];
        buf[i] = buf[length - i - 1];
        buf[length - i - 1] = aux;
    }

    buf[length] = '\0';

    return buf;
}

int cycle_number(int num, int boundary_top, int boundary_bottom){
    if (num > boundary_top){
        return boundary_bottom;
    }

    if (num < boundary_bottom){
        return boundary_top;
    }

    else return num;
}

void setup_screen_brightness(){
    DDRE |= _BV(3);
    TCNT3 = 0x0000;

    if (eeprom_read_from(199)==0x55){
        OCR3A = eeprom_read_from(200);
    }

    else {
        OCR3A = 0xFF / 2;
        eeprom_write_to(199, 0x55);
    } // a whatever value

    TCCR3A = _BV(COM3A1) | _BV(WGM30); // 8 BIT PWM mode, clear on match
    TCCR3B = _BV(CS30);                // no prescaler (aprox 15 kHz)
}

void set_screen_brightness(uint8_t brg){
    OCR3A = brg;
    eeprom_write_to(200, brg);
}

uint8_t get_screen_brightness(){
    return OCR3A;
}

// Check three values to see if they are the same. If so, we have a winner.
uint8_t tic_tac_toe_row(char chOne, char chTwo, char chThree){
    if ((chOne == chTwo) && (chOne == chThree)){
        if (chOne != ' ') return chOne;
    }

    return 0xFF;
}

// Check board for a win by looping through rows, columns and checking
// diagonals.
// If any of them are true, then there is a winning condition.
uint8_t tic_tac_toe_win(char grid[][3]){
    // Loop through the rows
    uint8_t aux;
    for (int i = 0; i < 3; i++){
        aux = tic_tac_toe_row(grid[i][0], grid[i][1], grid[i][2]);

        if (aux != 0xff){
            return aux;
        }
    }

    // Loop through the columns
    for (int i = 0; i < 3; i++){
        aux = tic_tac_toe_row(grid[0][i], grid[1][i], grid[2][i]);

        if (aux != 0xff){
            return aux;
        }
    }

    // Check diagonals
    aux = tic_tac_toe_row(grid[0][0], grid[1][1], grid[2][2]);
    if (aux != 0xff){
        return aux;
    }

    aux = tic_tac_toe_row(grid[0][2], grid[1][1], grid[2][0]);
    if (aux !=0xff){
        return aux;
    }

    return 0xff;
}

// TODO
void comunicacion( uint8_t c, uint8_t i ){

}

// Cambio password
void password_reload_screen(){
        char buf[10];

        lcd_clrscr();
        lcd_gotoxy(0, 0);
        lcd_puts_P("  Elija contrasena");

        switch (pass_screen.local_menu_pointer){
            case 0:
                lcd_gotoxy(7, 2);
                lcd_putc(RIGHT_ARROW);
                break;
            case 1:
                lcd_gotoxy(9, 2);
                lcd_putc(RIGHT_ARROW);
                break;
            case 2:
                lcd_gotoxy(11, 2);
                lcd_putc(RIGHT_ARROW);
                break;
            case 3:
                lcd_gotoxy(14, 4);
                lcd_putc(RIGHT_ARROW);
                break;
        }

        if (pass_screen.on_item){
            if (pass_screen.local_menu_pointer == 0){
                lcd_gotoxy(9, 2);
                lcd_putc(LEFT_ARROW);
                lcd_gotoxy(7, 2);
                lcd_putc(RIGHT_ARROW);
            }

            else if (pass_screen.local_menu_pointer == 1){
                lcd_gotoxy(11, 2);
                lcd_putc(LEFT_ARROW);
                lcd_gotoxy(9, 2);
                lcd_putc(RIGHT_ARROW);
            }

            else if (pass_screen.local_menu_pointer == 2){
                lcd_gotoxy(13, 2);
                lcd_putc(LEFT_ARROW);
                lcd_gotoxy(11, 2);
                lcd_putc(RIGHT_ARROW);
            }
        }

        lcd_gotoxy(8, 2);
        lcd_puts(convNum2str(buf, pass_screen.num1, 1));
      
        lcd_gotoxy(10, 2);
        lcd_puts(convNum2str(buf, pass_screen.num2, 1));

        lcd_gotoxy(12, 2);
        lcd_puts(convNum2str(buf, pass_screen.num3, 1));
        lcd_gotoxy(15, 4);
        lcd_puts_P("Confi"); 
}

// Cambio tengo que hacer el down up y press
void password_lcd_up(){
    if (pass_screen.on_item){
        if (pass_screen.local_menu_pointer == 0){
            if (pass_screen.num1 == 0) pass_screen.num1 = 10;
            pass_screen.num1--;
        }

        else if (pass_screen.local_menu_pointer == 1){
            if (pass_screen.num2 == 0) pass_screen.num2 = 10;
            pass_screen.num2--;
        }

        else if (pass_screen.local_menu_pointer == 2){
            if (pass_screen.num3 == 0) pass_screen.num3 = 10;
            pass_screen.num3--;
        }
    }

    else {
        if (pass_screen.local_menu_pointer == 0){
            pass_screen.local_menu_pointer = 4;
        }

        pass_screen.local_menu_pointer = (pass_screen.local_menu_pointer - 1)%4;
    }

    password_reload_screen();
}

void password_lcd_down(){
    if (pass_screen.on_item){
        if (pass_screen.local_menu_pointer == 0){
            pass_screen.num1 = (pass_screen.num1 + 1) % 10;
        }
        else if (pass_screen.local_menu_pointer == 1){
            pass_screen.num2 = (pass_screen.num2 + 1) % 10;
        }
        else if (pass_screen.local_menu_pointer == 2){
            pass_screen.num3 = (pass_screen.num3 + 1) % 10;
        }
    }

    else {
       pass_screen.local_menu_pointer = (pass_screen.local_menu_pointer + 1)%4;
    }

    password_reload_screen();
}

void password_lcd_button_press(){
    if (pass_screen.local_menu_pointer == 3){
        if (pass_screen.num1 == 2 && pass_screen.num2 == 2 &&
            pass_screen.num3 == 2){
            current_screen = LIST;
            pass_screen.on_item = true;
        }

        else {
            lcd_clrscr();
            lcd_gotoxy(0, 0);

            lcd_puts_P("WRONG");
            lcd_gotoxy(0, 1);

            lcd_puts_P("Please try again");
            delay (2000);
        }
    }

    lcd_reload_screen();
}

void game_reload_screen(){
    int i, j;
    uint8_t winner;

    for (i = 0; i < 3; i++){
        lcd_gotoxy(4, i);

        for(j = 0; j < 3; j++){
            lcd_putc(game_screen.map[i][j]);
        }
    }

    lcd_gotoxy(4,3);
    lcd_puts("BACK");

    if (game_screen.pointer < 9){
        lcd_gotoxy(3,3);
        lcd_putc(' ');
        lcd_gotoxy(4 + game_screen.pointer / 3, game_screen.pointer % 3);
        lcd_putc(game_screen.turn+RIGHT_ARROW_UND);
    }

    else {
        lcd_gotoxy(3,3);
        lcd_putc(RIGHT_ARROW);
    }

    winner = tic_tac_toe_win(game_screen.map);
    if (winner != 0xff){
        lcd_gotoxy(10,1);
        lcd_puts("Winner");
        lcd_gotoxy(10,2);
        lcd_puts("is ");
        lcd_putc(winner);
    }
}

void list_reload_screen(){
    uint8_t i;
    char buf[10];
    lcd_clrscr();

    // Vamos a ir recargando línea a línea de las 4 del display
    for (i = 0; i < 4; i++){
        lcd_gotoxy(1, i);
        lcd_puts(list_screen.entries[i + list_screen.global_menu_pointer]);

        // Si estamos en el menu del SAVE a EEPROM
        if(list_screen.global_menu_pointer + i == 8){
            if(list_screen.on_save){
                lcd_puts(" ");
                lcd_putc(LEFT_ARROW);
                if(list_screen.save_memory_selected == 4){
                    lcd_puts("BACK");
                }

                else{
                    lcd_puts(nombreCoche);
                }

                lcd_putc(RIGHT_ARROW);
                if(list_screen.tick){
                    lcd_putc(GOOD_TICK);
                    list_screen.tick = 0;
                                       
                }
            }

            else {
                lcd_puts("  ");
                if(list_screen.save_memory_selected == 4){
                    lcd_puts("BACK");
                }
                else {
                    lcd_puts(nombreCoche);
                }
            }
        }

        // Si estamos en el menu del LOAD a EEPROM
        if (list_screen.global_menu_pointer + i == 9){
            if (list_screen.on_load){ // Cuando estan ON_LOAD tiene las flechas 
                                      // activas para cambiarlos.
                lcd_puts(" ");
                lcd_puts(convNum2str(buf, list_screen.load_memory_selected, 1));
                lcd_putc(LEFT_ARROW);

                if (list_screen.load_memory_selected == 4){
                    lcd_puts("BACK");
                }

                else { // La asignacion de nombre lo hago en el up/down
                    lcd_puts(nombreCoche);
                }

                lcd_putc(RIGHT_ARROW);
                if (list_screen.tick){
                    lcd_putc(GOOD_TICK);
                    list_screen.tick = 0;
                }
            }

            else {
                lcd_puts(" ");
                lcd_puts(convNum2str(buf, list_screen.load_memory_selected, 1));
                if (list_screen.save_memory_selected == 4){
                    lcd_puts("BACK");
                }

                else {
                    lcd_puts(nombreCoche);
                }
            }
        }

        /*
            if (list_screen.global_menu_pointer + i == 11 &&
                list_screen.seniales_lentas){
                current_screen = SENIALESLENTAS;
                lcd_reload_screen();
            }
        */

        lcd_gotoxy(1, i);
    }

    lcd_gotoxy(0, list_screen.local_menu_pointer);
    lcd_putc(RIGHT_ARROW);

    // Si estamos en el menu del Brillo del LCD
    if (list_screen.global_menu_pointer == 7){
        lcd_gotoxy(13, 3);
        lcd_puts(convNum2str(buf,5 - get_screen_brightness() / 25, 2));

        if (list_screen.on_brightness){
            lcd_gotoxy(12, 3);
            lcd_putc(LEFT_ARROW);
            lcd_gotoxy(15, 3);
            lcd_putc(RIGHT_ARROW);
        }
    }
}

void pwm_reload_screen(){
    char buf[10];
    lcd_clrscr();
    lcd_gotoxy(1, 0);
    lcd_puts_P("MODE ");

    switch (pwm_screen.pwm_pins[pwm_screen.pwm_channel].en){
        case 0:
            lcd_puts_P("PWM");
            break;
        case 1:
            lcd_puts_P(" ON");
            break;
        case 2:
            lcd_puts_P("OFF");
            break;
        default:
            configure_pwm_pin(pwm_screen.pwm_pins, pwm_screen.pwm_channel,0, 0);
            lcd_puts_P("OFF");
            break;
    }

    lcd_gotoxy(1, 1);
    lcd_puts_P("FRQ= ");
    lcd_puts(convNum2str(buf, pwm_screen.pwm_pins[pwm_screen.pwm_channel].frq /
                                                                        10, 3));
    lcd_puts(".");
    lcd_puts(convNum2str(buf, pwm_screen.pwm_pins[pwm_screen.pwm_channel].frq %
                                                                        10, 1));
    lcd_gotoxy(12, 1);
    lcd_puts_P("Hz");

    if (pwm_screen.freq_fine){
        lcd_puts_P("(f)");
    }

    lcd_gotoxy(1, 2);
    lcd_puts_P("DTY= ");
    lcd_puts(convNum2str(buf, pwm_screen.pwm_pins[pwm_screen.pwm_channel].dty,
                                                                            3));
    lcd_gotoxy(10, 2);
    lcd_puts_P("%");
    lcd_gotoxy(1, 3);
    lcd_puts_P("PHS= ");

    if (pwm_screen.pwm_pins[pwm_screen.pwm_channel].phase >= 0){
        lcd_puts_P("+");
    }

    else {
        lcd_puts_P("-");
    }

    lcd_puts(convNum2str(buf, pwm_screen.pwm_pins[pwm_screen.pwm_channel].phase,
                                                                            2));
    lcd_gotoxy(10, 3);
    lcd_puts_P("%");
    lcd_gotoxy(16, 3);
    lcd_puts_P("BACK");

    if(pwm_screen.local_menu_pointer < 4){
        lcd_gotoxy(0, pwm_screen.local_menu_pointer);
    }

    else {
        lcd_gotoxy(15, 3);
    }

    lcd_putc(RIGHT_ARROW);

    if (pwm_screen.on_item){
        if (pwm_screen.local_menu_pointer == 1){ //Freq
            lcd_gotoxy(5, pwm_screen.local_menu_pointer);
            lcd_putc(LEFT_ARROW);
            lcd_gotoxy(11, pwm_screen.local_menu_pointer);
            lcd_putc(RIGHT_ARROW);
        }

        else{
            lcd_gotoxy(5, pwm_screen.local_menu_pointer);
            lcd_putc(LEFT_ARROW);
            lcd_gotoxy(9, pwm_screen.local_menu_pointer);
            lcd_putc(RIGHT_ARROW);
        }
    }

    lcd_gotoxy(14, 0);
    lcd_puts_P("PWM: ");
    lcd_puts(convNum2str(buf, pwm_screen.pwm_channel + 1, 1));
}

void lcd_screensaver(){
    lcd_clrscr();
    lcd_gotoxy(0, 0);

    lcd_puts_P("  GranaSAT PWM BOX");
    lcd_gotoxy(0, 1);

    lcd_puts_P("     HW-Ver:");
    lcd_puts_P(HW_VERSION);
    lcd_gotoxy(0, 2);

    lcd_puts_P("     SW-Ver:");
    lcd_puts_P(SW_VERSION);
    lcd_gotoxy(0, 3);

    lcd_puts_P("  granasat.ugr.es");
}

void lcd_menu_init(pwm_pin_TD *pwm_pins){
    // Only in test board
    pinMode(41, OUTPUT);
    digitalWrite(41, LOW);
    pinMode(46, OUTPUT);
    digitalWrite(46, LOW);
    pinMode(47, OUTPUT);
    digitalWrite(47, LOW);
    pinMode(48, OUTPUT);
    digitalWrite(48, LOW);
    pinMode(49, OUTPUT);
    digitalWrite(49, LOW);
    lcd_init(LCD_DISP_ON);
    lcd_screensaver();
    delay(BOOT_DELAY_MS);

    //Hasta aqui imprime todo en el LCD en su fila.

    lcd_command(_BV(LCD_CGRAM)); /* set CG RAM start address 0 */
    int i, j;
    for (i = 0; i < 8; i++){
        lcd_data(pgm_read_byte_near(&rightArrow[i]));
    }

    for (i = 0; i < 8; i++){
        lcd_data(pgm_read_byte_near(&leftArrow[i]));
    }

    for (i = 0; i < 8; i++){
        lcd_data(pgm_read_byte_near(&upArrow[i]));
    }

    for (i = 0; i < 8; i++){
        lcd_data(pgm_read_byte_near(&downArrow[i]));
    }

    for (i = 0; i < 8; i++){
        lcd_data(pgm_read_byte_near(&goodTick[i]));
    }

    for (i = 0; i < 8; i++){
        lcd_data(pgm_read_byte_near(&rightArrow_und[i]));
    }

    for (i = 0; i < 8; i++){
        lcd_data(pgm_read_byte_near(&leftArrow_und[i]));
    }

    for (i = 0; i < 8; i++){
        lcd_data(pgm_read_byte_near(&und[i]));
    }

    pwm_to_eeprom_t aux[8];
    pwm_to_eeprom_t data[8];
    char auxNombre[12];

    /*
        strcpy(list_screen.entries[0], "PWM 1 Seat Leon");
        strcpy(list_screen.entries[1], "PWM 2 Renault Clio");
        strcpy(list_screen.entries[2], "PWM 3 Ferrari");
        strcpy(list_screen.entries[3], "PWM 4"); 
        strcpy(list_screen.entries[4], "PWM 5");
        strcpy(list_screen.entries[5], "PWM 6");
        strcpy(list_screen.entries[6], "PWM 7");
        strcpy(list_screen.entries[7], "PWM 8");
    */

    strcpy(list_screen.entries[8], "SAVE");
    strcpy(list_screen.entries[9], "LOAD");
    strcpy(list_screen.entries[10], "BRIGHTNESS");
    strcpy(list_screen.entries[11], "Senales lentas"); 

    pwm_screen.pwm_pins = pwm_pins;
    obtenerNombreCoche(nombreCoche,0);

    eeprom_load_pwms(data, 0);

    asignarnombre(list_screen.entries, data);

    for (i = 0; i < 8; i++){
        configure_pwm_pin(pwm_screen.pwm_pins, i, data[i].freq, data[i].dty);
        pwm_pin_enable(pwm_screen.pwm_pins, i, data[i].en);
    }

    sync_pwms(pwm_screen.pwm_pins);

    list_screen.load_memory_selected = 0; 
    list_screen.global_menu_pointer = 0;
    list_screen.local_menu_pointer = 0;
    list_screen.global_menu_pointer_max = 8; // Change to defines inicialmente 7
    list_screen.local_menu_pointer_max = 4;
    list_screen.seniales_lentas = false;
    lenta_screen.local_menu_pointer = 0;
    lenta_screen.on_item = 0;

    for (i = 0; i < 3; i++){
        for(j = 0;j < 3; j++){
            game_screen.map[i][j] = ' ';
        }
    }

    pass_screen.num1 = 2;
    pass_screen.num2 = 2;
    pass_screen.num3 = 2;
    pass_screen.on_item = false;
    pass_screen.local_menu_pointer = 0;
    current_screen = LIST; // Cambio PWM_MENUPASSWORD
    // password_reload_screen(); // Comentar abajo y descomentar esto 
    lcd_reload_screen();
    // list_reload_screen(); // Esto estaba sin comentar
    // setup_screen_brightness();
}

void asignarnombre(list_menu_td *nombre, pwm_to_eeprom_t *data){
    char aux[19];
    char numero[3];

    for (int i = 0; i < 8; i++){
        strcpy(aux, "PWM ");
        // strcpy(list_screen.entries[i+5], i);
        // numero = i + '0';
        
        // aux[5] = ;
        strcat(aux, convNum2str(numero, i + 1, 1));
        strcat(aux, " ");
        strcat(aux, data[i].nombre);
        strncpy(nombre->entries[i], aux, 18);
    }
}



void lcd_quick_button(){
    if (current_screen == PWM_MENU){
        if (pwm_screen.freq_fine == 1){
            pwm_screen.freq_fine == 0;
        }
        else {
            pwm_screen.freq_fine == 1;
        }
    }
}

void lcd_reload_screen(){
    if (current_screen == PWM_MENU){
        if ( pass_screen.on_item == false){
            pass_screen.local_menu_pointer = 0;
            current_screen = PASSWORD;
            password_reload_screen();
        }

        pwm_reload_screen();
    }

    if (current_screen == LIST){
        list_reload_screen();
    }

    if (current_screen == GAME_SCREEN){
        game_reload_screen();
    }

    if(current_screen == PASSWORD){
        password_reload_screen();
    }

    if(current_screen == SENIALESLENTAS){
        seniales_lentas_reload();
    }
}
void lcd_button_press(){
    if (current_screen == LIST){
        list_lcd_button_press();
    }

    else if (current_screen == PWM_MENU){
        if (pass_screen.on_item == false){
            pass_screen.local_menu_pointer = 0;
            current_screen = PASSWORD;
            password_reload_screen();
        }

        pwm_lcd_button_press();
    }

    else if(current_screen == GAME_SCREEN){
        game_lcd_button_press();
    }

    else if(current_screen == PASSWORD){
        password_lcd_button_press();
    }

    else if(current_screen == SENIALESLENTAS){
        seniales_lentas_press();
    }
}

void lcd_up(uint8_t velocity){
    if (current_screen == LIST){
        list_lcd_up();
    }

    else if (current_screen == PWM_MENU){
        pwm_lcd_up(velocity);
    }

    else if (current_screen == GAME_SCREEN){
        game_lcd_down();
    }

    else if (current_screen == PASSWORD){
        password_lcd_up();
    }

    else if(current_screen == SENIALESLENTAS){
        seniales_lentas_up();
    }
}

void lcd_down(uint8_t velocity){
    if (current_screen == LIST){
        list_lcd_down();
    }

    else if (current_screen == PWM_MENU){
        pwm_lcd_down(velocity);
    }

    else if (current_screen == GAME_SCREEN){
        game_lcd_up();
    }

    else if (current_screen == PASSWORD){
        password_lcd_down();
    }

    else if (current_screen == SENIALESLENTAS){
        seniales_lentas_down();
    }
}

void game_lcd_up(){
    game_screen.pointer = cycle_number(game_screen.pointer + 1, 9, 0);
    lcd_reload_screen();
}

void game_lcd_down(){
    game_screen.pointer = cycle_number(game_screen.pointer - 1, 9, 0);
    lcd_reload_screen();
}

void game_lcd_button_press(){
    if (game_screen.pointer > 8){
        current_screen = LIST;
        lcd_reload_screen();
        return;
    }

    if (game_screen.map[game_screen.pointer % 3][game_screen.pointer/3] == ' '){
        game_screen.map[game_screen.pointer % 3][game_screen.pointer/3] = 
                                                               game_screen.turn;
        game_screen.turn ^= 1;
    }

    lcd_reload_screen();
}

void list_lcd_button_press(){
    uint8_t select = list_screen.global_menu_pointer +
                                                list_screen.local_menu_pointer;
    pwm_to_eeprom_t aux[8];
    uint8_t i;
    char nombreAuxiliar[19];

    switch (select){
        case 9: // Load data
            if (list_screen.on_load){
                if (list_screen.load_memory_selected == 4){
                    list_screen.on_load = 0;
                }

                else {
                    // obtenerNombreCoche(nombreCoche, list_screen.load_memory_selected);
                    eeprom_load_pwms(aux, list_screen.load_memory_selected);
                    asignarnombre(list_screen.entries, aux);

                    for (i = 0; i < 8; i++){
                        configure_pwm_pin(pwm_screen.pwm_pins, i, aux[i].freq, 
                                          aux[i].dty);
                        pwm_pin_enable(pwm_screen.pwm_pins, i, aux[i].en);
                    }

                    sync_pwms(pwm_screen.pwm_pins);
                    list_screen.tick = 1;
                    list_screen.on_load = 0; // Con esto se desactiva el menu tras cargar la configuración de EEPROM seleccionada
                }
            }

            else {
                list_screen.on_load = 1;
                list_screen.tick = 0;
            }

            list_reload_screen();
            // eeprom_load_pwms(aux, 0);

            break;
        case 8: // Save data
            if (list_screen.on_save){
                if (list_screen.load_memory_selected == 4){ // Esto antes funcionaba con save_memory_selected
                    list_screen.on_save = 0; // Pero lo pongo con load debido al uso que le doy
                }

                else {
                    for (i = 0; i < 8; i++){
                        aux[i].freq = pwm_screen.pwm_pins[i].frq;
                        aux[i].dty = pwm_screen.pwm_pins[i].dty;
                        aux[i].en = pwm_screen.pwm_pins[i].en;
                        aux[i].phs = pwm_screen.pwm_pins[i].phase;

                        strcpy(nombreAuxiliar, list_screen.entries[i]);

                        for (int j = 0; j <12; j++){ 
                            aux[i].nombre[j] = nombreAuxiliar[j+6];
                        }
                    }

                    eeprom_save_pwms(aux, list_screen.load_memory_selected);
                    sync_pwms(pwm_screen.pwm_pins);
                    list_screen.tick=1;
                    list_screen.on_save = 0; // Con esto se desactiva el menu tras guardar la configuracion de EEPROM seleccionada
                }
            }

            else {
                list_screen.on_save = 1; 
                // list_screen.tick = 0;
            }

            list_reload_screen();
            break;
        case 10: // brightness control
            list_screen.on_brightness ^= 1;
            list_reload_screen();
            break;
        case 11:
            //Cambio aqui tendria que llamar a la funcion de las seniales
            if (list_screen.seniales_lentas == false) {
                list_screen.seniales_lentas = true;
                current_screen = SENIALESLENTAS;
            }

            seniales_lentas_reload();
            break;
        //cambio seniales lenta
        default:
            current_screen = PWM_MENU;
            pwm_screen.local_menu_pointer = 0;
            pwm_screen.pwm_channel = select;
            pwm_screen.on_item = false;
            pwm_reload_screen();
            break;
    }
    
    if (list_screen.game){
        current_screen = GAME_SCREEN;
        lcd_clrscr();
        lcd_reload_screen();
    }
}

void list_lcd_up(){
    uint16_t aux;
    list_screen.game = 0;

    if (list_screen.on_save){ // Solo se pueden guardar las 8 PWM
        /*
            list_screen.save_memory_selected++;
            list_screen.save_memory_selected = cycle_number(list_screen.save_memory_selected, 4, 0);
        */
        list_reload_screen();
        return;
    }

    if (list_screen.on_load){
        if (list_screen.load_memory_selected == 4 ){
            list_screen.load_memory_selected = obtenerNumCoches()-1
        }

        list_screen.load_memory_selected--;

        if ( list_screen.load_memory_selected < 0 ){
            list_screen.load_memory_selected = 0;
        }

        obtenerNombreCoche(nombreCoche, list_screen.load_memory_selected);

        list_reload_screen();
        return;
    }

    if (list_screen.on_brightness){
        set_screen_brightness(get_screen_brightness() + 25);

        if (get_screen_brightness() % 25 != 0){
            set_screen_brightness(get_screen_brightness() +
                                                (get_screen_brightness() % 25));
        }

        if(get_screen_brightness() > 125){
            set_screen_brightness(0);
        }

        list_reload_screen();

        return;
    }

    if ((list_screen.global_menu_pointer <= 0) &&
        (list_screen.local_menu_pointer <= 0)){
        return;
    }

    if (list_screen.local_menu_pointer <= 0){
        list_screen.global_menu_pointer--;
        list_reload_screen();
    }

    /*
        if ( list_screen.seniales_lentas )// que no haga nada
        {
            list_reload_screen();
            list_screen.global_menu_pointer = 11;
        }
    */

    else {
        lcd_gotoxy(0, list_screen.local_menu_pointer);
        lcd_putc(' ');

        list_screen.local_menu_pointer--;

        lcd_gotoxy(0, list_screen.local_menu_pointer);
        lcd_putc(RIGHT_ARROW);
    }
}

void list_lcd_down(){
    uint16_t aux;
    list_screen.game = 0;

    if (list_screen.on_save){ //Solo se guardan las 8 PWM
        /*
            list_screen.save_memory_selected--;
            list_screen.save_memory_selected = cycle_number(list_screen.save_memory_selected, 4, 0);
        */

        list_reload_screen();
        return;
    }

    if (list_screen.on_load){
        list_screen.load_memory_selected++;

        if ((list_screen.load_memory_selected - 1) > obtenerNumCoches()){
            list_screen.load_memory_selected = 4;
        }

        obtenerNombreCoche(nombreCoche, list_screen.load_memory_selected);

        list_reload_screen();

        return;
    }

    if (list_screen.on_brightness){
        set_screen_brightness(get_screen_brightness() - 25);

        if (get_screen_brightness() % 25 != 0){
            set_screen_brightness(get_screen_brightness() -
                                                (get_screen_brightness() % 25));
        }

        if (get_screen_brightness() > 125){
            set_screen_brightness(125);
        }

        list_reload_screen();

        return;
    }

    if ((list_screen.global_menu_pointer >=
         list_screen.global_menu_pointer_max) &&
        (list_screen.local_menu_pointer >=
         list_screen.local_menu_pointer_max - 1)){
        list_screen.game = 0;
        return;
    }

    if (list_screen.local_menu_pointer >= list_screen.local_menu_pointer_max -
                                                                             1){
        list_screen.global_menu_pointer++;
        list_reload_screen();
    }

    /*
        if (list_screen.seniales_lentas){
            // Que no haga nada
            list_reload_screen();
            list_screen.global_menu_pointer = 11;
        }
    */

    else {
        lcd_gotoxy(0, list_screen.local_menu_pointer);
        lcd_putc(' ');

        list_screen.local_menu_pointer++;

        lcd_gotoxy(0, list_screen.local_menu_pointer);
        lcd_putc(RIGHT_ARROW);
    }
}

void pwm_lcd_button_press(){
    switch (pwm_screen.local_menu_pointer){
        case 0:
            pwm_screen.on_item ^= 1;
            pwm_reload_screen();
            break;
        case 1: // TODO, make enum
            if ((pwm_screen.on_item == 1) && (pwm_screen.freq_fine == 0)){
                pwm_screen.freq_fine = 1;
                pwm_reload_screen();
                uart_puts("on1\r\n");
            }

            else {
                uart_puts("on3\r\n");
                pwm_screen.on_item ^= 1;
                pwm_screen.freq_fine = 0;
                pwm_reload_screen();
            }
            break;
        case 2:
            pwm_screen.on_item ^= 1;
            pwm_reload_screen();
            break;
        case 3:
            sync_pwms(pwm_screen.pwm_pins);
            pwm_screen.on_item ^= 1;
            pwm_reload_screen();
            break;
        case 4:
            current_screen = LIST;
            list_reload_screen();
            break;
    }
};

void pwm_lcd_up(uint8_t velocity){
    int aux;

    if (!pwm_screen.on_item){
        if (pwm_screen.local_menu_pointer != 0){
            pwm_screen.local_menu_pointer = (pwm_screen.local_menu_pointer - 1);
        }

        else {
            pwm_screen.local_menu_pointer = 4;
        }
    }

    else {
        if (pwm_screen.local_menu_pointer == 0){
            pwm_screen.pwm_pins[pwm_screen.pwm_channel].en =
                (uint8_t)cycle_number(((int)pwm_screen.pwm_pins[pwm_screen.pwm_channel].en) + 1, 2, 0);
        }

        if (pwm_screen.local_menu_pointer == 1){
            aux = (int)pwm_screen.pwm_pins[pwm_screen.pwm_channel].frq;

            if (!pwm_screen.freq_fine){
                switch (velocity){
                    case 0:
                        aux = aux + 10;
                        break;
                    case 1:
                        aux = aux + 50;
                        break;
                    case 2:
                        aux = aux + 100;
                        break;
                    default:
                        break;
                }
            }

            else {
                aux = aux + 1;
            }

            aux = cycle_number(aux, 4000, 0);
            configure_pwm_pin(pwm_screen.pwm_pins, pwm_screen.pwm_channel,
                              (uint16_t)aux,
                              pwm_screen.pwm_pins[pwm_screen.pwm_channel].dty);
        }

        if (pwm_screen.local_menu_pointer == 2){
            aux = pwm_screen.pwm_pins[pwm_screen.pwm_channel].dty;
            aux = aux + 1;
            aux = cycle_number(aux, 100, 0);
            configure_pwm_pin(pwm_screen.pwm_pins, pwm_screen.pwm_channel,
                              pwm_screen.pwm_pins[pwm_screen.pwm_channel].frq,
                              (uint16_t)aux);
        }

        if (pwm_screen.local_menu_pointer == 3){
            aux = pwm_screen.pwm_pins[pwm_screen.pwm_channel].phase;
            aux = aux + 1;
            aux = cycle_number(aux, 99, -99);
            configure_pwm_phase(pwm_screen.pwm_pins, pwm_screen.pwm_channel,
                                aux);
        }
    }

    pwm_reload_screen();
}

void pwm_lcd_down(uint8_t velocity){
    int aux;

    if (!pwm_screen.on_item){
        if (pwm_screen.local_menu_pointer != 4){
            pwm_screen.local_menu_pointer = (pwm_screen.local_menu_pointer + 1);
        }
        else {
            pwm_screen.local_menu_pointer = 0;
        }
    }

    else {
        if (pwm_screen.local_menu_pointer == 0){
            pwm_screen.pwm_pins[pwm_screen.pwm_channel].en =
                (uint8_t)cycle_number(((int)pwm_screen.pwm_pins[pwm_screen.pwm_channel].en) - 1, 2, 0);
        }

        if (pwm_screen.local_menu_pointer == 1){
            aux = (int)pwm_screen.pwm_pins[pwm_screen.pwm_channel].frq;
            if (!pwm_screen.freq_fine){
                switch (velocity){
                    case 0:
                        aux = aux - 10;
                        break;
                    case 1:
                        aux = aux - 50;
                        break;
                    case 2:
                        aux = aux - 100;
                        break;
                    default:
                        break;
                }
            }

            else{
                aux = aux - 1;
            }

            aux = cycle_number(aux, 4000, 0);
            configure_pwm_pin(pwm_screen.pwm_pins, pwm_screen.pwm_channel,
                              (uint16_t)aux,
                              pwm_screen.pwm_pins[pwm_screen.pwm_channel].dty);
        }

        if (pwm_screen.local_menu_pointer == 2){
            aux = (int)pwm_screen.pwm_pins[pwm_screen.pwm_channel].dty;
            aux = aux - 1;
            aux = cycle_number(aux, 100, 0);
            configure_pwm_pin(pwm_screen.pwm_pins, pwm_screen.pwm_channel,
                              pwm_screen.pwm_pins[pwm_screen.pwm_channel].frq,
                              (uint16_t)aux);
        }

        if (pwm_screen.local_menu_pointer == 3){
            aux = pwm_screen.pwm_pins[pwm_screen.pwm_channel].phase;
            aux = aux - 1;
            aux = cycle_number(aux, 99, -99);
            configure_pwm_phase(pwm_screen.pwm_pins, pwm_screen.pwm_channel,aux);
        }
    }

    pwm_reload_screen();
}

// Señales lentas llamar funcion idea
void seniales_lentas_press(){
    if ( lenta_screen.on_item == 1){
        lenta_screen.on_item = 0;
    }

    else { // lenta_screen.on_item == 0
        // Llamada funcion ford Timer1.attachInterrupt(senialeslentas_ford);
        if (lenta_screen.local_menu_pointer == 0 ) lenta_screen.on_item = 1;
        // Llamada funcion Valeo
        if (lenta_screen.local_menu_pointer == 1 ) lenta_screen.on_item = 1;
        // Llamada funcion Renault
        if (lenta_screen.local_menu_pointer == 2 ) lenta_screen.on_item = 1;

        if (lenta_screen.local_menu_pointer == 3 ){
            // lcd_clrscr();
            // lenta_screen.on_item = 0;
            list_screen.seniales_lentas = false;
            current_screen = LIST;
            list_reload_screen();
        }
    }

    lcd_reload_screen();
}

void seniales_lentas_up(){
    if (lenta_screen.on_item == 0 && lenta_screen.local_menu_pointer > 0){
        lenta_screen.local_menu_pointer = lenta_screen.local_menu_pointer - 1;
    } 
    seniales_lentas_reload();

}

void seniales_lentas_down(){
    if (lenta_screen.on_item == 0){
        lenta_screen.local_menu_pointer =
                                      (lenta_screen.local_menu_pointer + 1) % 4;
    }

    seniales_lentas_reload();
}

void seniales_lentas_reload(){
    if (lenta_screen.on_item == 0){
        lcd_clrscr();
        lcd_gotoxy(0, 0);

        lcd_puts_P("Modo Seniales Lentas");
        lcd_gotoxy(1, 1);
        lcd_puts_P("Ford");
        lcd_gotoxy(1, 2);
        lcd_puts_P("ValeoPRO01");
        lcd_gotoxy(1, 3);
        lcd_puts_P("Renault");
        lcd_gotoxy(16,3);
        lcd_puts("BACK");

        if (lenta_screen.local_menu_pointer == 0){
            lcd_gotoxy(0, 1);
            lcd_putc(RIGHT_ARROW);
        }

        if (lenta_screen.local_menu_pointer == 1){
            lcd_gotoxy(0, 2);
            lcd_putc(RIGHT_ARROW);
        }

        if (lenta_screen.local_menu_pointer == 2){
            lcd_gotoxy(0, 3);
            lcd_putc(RIGHT_ARROW);
        }

        if (lenta_screen.local_menu_pointer == 3){
            lcd_gotoxy(15, 3);
            lcd_putc(RIGHT_ARROW);
        }
    }

    if (lenta_screen.on_item == 1){
        lcd_clrscr();
        lcd_gotoxy(0, 0);

        lcd_puts_P("Modo Seniales Lentas");

        if (lenta_screen.local_menu_pointer == 0){
            lcd_gotoxy(5, 1);
            lcd_puts_P("Ejecutando");
            lcd_gotoxy(7, 2);
            lcd_puts_P("Ford");
            lcd_gotoxy(15,3);
            lcd_putc(RIGHT_ARROW);
            lcd_gotoxy(16,3);
            lcd_puts("BACK");
        }

        if (lenta_screen.local_menu_pointer == 1){
            lcd_gotoxy(5, 1);
            lcd_puts_P("Ejecutando");
            lcd_gotoxy(5, 2);
            lcd_puts_P("ValeoPRO01");
            lcd_gotoxy(15,3);
            lcd_putc(RIGHT_ARROW);
            lcd_gotoxy(16,3);
            lcd_puts("BACK");
        }

        if (lenta_screen.local_menu_pointer == 2){
            lcd_gotoxy(5, 1);
            lcd_puts_P("Ejecutando");
            lcd_gotoxy(6, 2);
            lcd_puts_P("Renault");
            lcd_gotoxy(15,3);
            lcd_putc(RIGHT_ARROW);
            lcd_gotoxy(16,3);
            lcd_puts("BACK");
        }
    }
}