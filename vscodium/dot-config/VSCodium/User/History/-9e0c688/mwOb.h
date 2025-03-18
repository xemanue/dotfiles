/* 
 * Copyright (C) GranaSAT - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Luis Sanchez <luissanv@ugr.es>, August 2018
 */

/**
 * @file
 * @brief Manages the control timer and generates the PWM
 */

#ifndef LCD_MENU_H
#define LCD_MENU_H

#include <Arduino.h>
#include <inttypes.h>
#include "config.h"
#include "lcd.h"
#include "pwm_gen.h"
#include "virtual_PWM.h"
#include "eeprom_control.h"
#include "IO_control.h"

#define LIST 0
#define PWM_MENU 1
#define GAME_SCREEN 2
#define PASSWORD 3
#define SENIALESLENTAS 4

// Apparently, if you use a C library, C++ compiles it using name mangling
// This prevents it
#ifdef __cplusplus
    extern "C" {
#endif

/**
 * @brief Contains the information needed to display the password screen
 */
typedef struct {
    uint8_t num1;
    uint8_t num2;
    uint8_t num3;
    bool on_item;
    uint8_t local_menu_pointer;
} pass_menu_td;

typedef struct {
    bool on_item;
    uint8_t local_menu_pointer;
} lenta_menu_td;

typedef struct {
    char entries[12][19]; // Antes matriz de 19 no se porque
    uint8_t on_brightness;
    uint8_t on_save;
    uint8_t save_memory_selected;
    uint8_t on_load;
    int8_t load_memory_selected;
    uint8_t tick;
    uint8_t global_menu_pointer;
    uint8_t global_menu_pointer_max;
    uint8_t local_menu_pointer;
    uint8_t local_menu_pointer_max;
    uint8_t game;
    uint8_t password;
    bool seniales_lentas;
} list_menu_td;

typedef struct {
    uint8_t pwm_channel;
    uint8_t local_menu_pointer;
    uint8_t on_item;
    uint8_t freq_fine;
    pwm_pin_TD * pwm_pins;
} pwm_menu_td;

typedef struct {
    uint8_t pointer;
    uint8_t turn;
    uint8_t map[3][3];
} game_td;

extern uint8_t current_screen;
extern list_menu_td list_screen;
extern pwm_menu_td pwm_screen;

/**
 * @brief Initializes the screen
 * 
 * @param[in] pwm_pins PWMs to be displayed in the PWM menu
 */
void lcd_menu_init(pwm_pin_TD *pwm_pins);

/**
 * @brief Processes each button press in general
 */
void lcd_button_press();

/**
 * @brief Processes each scroll up in general
 * 
 * @param[in] velocity Speed at which the rotary encoder is scrolled
 */
void lcd_up(uint8_t velocity);

/**
 * @brief Processes each scroll down in general
 * 
 * @param[in] velocity Speed at which the rotary encoder is scrolled
 */
void lcd_down(uint8_t velocity);

/**
 * @brief Initializes the screensaver
 */
void lcd_screensaver();

/**
 * @brief Processes a button press on the list screen
 */
void list_lcd_button_press();

/**
 * @brief Processes an up scroll on the list screen
 */
void list_lcd_up();

/**
 * @brief Processes a down scroll on the list screen
 */
void list_lcd_down();

/**
 * @brief Handles reloading the screen
 */
void lcd_reload_screen();

/**
 * @brief Processes a button press on the PWM screen
 */
void pwm_lcd_button_press();

/**
 * @brief Processes an up scroll on the list screen
 * 
 * @param[in] velocity Speed at which the rotary encoder is scrolled
 */
void pwm_lcd_up(uint8_t velocity);

/**
 * @brief Processes a down scroll on the list screen
 * 
 * @param[in] velocity Speed at which the rotary encoder is scrolled
 */
void pwm_lcd_down(uint8_t velocity);

/**
 * @brief Processes a button press on the game screen
 */
void game_lcd_button_press();

/**
 * @brief Processes an up scroll on the game screen
 */
void game_lcd_up();

/**
 * @brief Processes a down scroll on the game screen
 */
void game_lcd_down();


void asignarnombre(list_menu_td *nombre, pwm_to_eeprom_t *data);

void comunicacion(uint8_t c, uint8_t i);
void setup_screen_brightness();
void set_screen_brightness(uint8_t brg);
uint8_t get_screen_brightness();
void lcd_quick_button();


#ifdef __cplusplus
    }
#endif

#endif /* LCD_MENU_H */
