/* Copyright (C) GranaSAT - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Luis Sanchez <luissanv@ugr.es>, August 2018
 */
#ifndef IO_CONTROL_H
#define IO_CONTROL_H
#include <Arduino.h>
#include <inttypes.h>
#include "config.h"
#include "lifo_mem.h"
#include "lcd_menu.h"
#include "uart_control.h"
#include "pwm_gen.h"
#include "eeprom_control.h"
/*!
 * @file
 * @defgroup IO_control <IO_control.h>
 * @code #include <IO_control.h> @endcode
 *
 * @brief Short module to setup and process IO events 
 * 
 * Sets up all the neccesary interrupts for the IO lines (roraty and push button)
 * as well as the required functions to process such events
 */

/*!
 * @file
 * @brief Sets up and and manages action to all the IO drom the user (rotary)
 */
#ifdef __cplusplus
extern "C" { //apparently if you used a C library C++ compile with mangle its name unless you use "extern C", fuck C++
#endif

/**@{*/
#define DIR_NONE 0x0
// Clockwise step.
#define DIR_CW 0x10
// Counter-clockwise step.
#define DIR_CCW 0x20
/**
 * Types of events numbered
 */
enum EventType{
    /*@{*/
    MOVEMENT_UP = 0, /**< Rotary encoder was turned clockwise */
    MOVEMENT_DOWN,  /**< Rotary encoder was turned anticlockwise */
    BUTTON_PUSH,    /**< Rotary encoder button was pressed */
    QUICK_BUTTON_PUSH, /**< Fast button push */
    UART_RX, /**< Received a message from uart */
    /*@}*/
};

/**
 * Types of rotary velocity numbered
 */
enum RotaryVelocity{
    /*@{*/
    ROTARY_SLOW = 0, /**< Rotary encoder was turned clockwise */
    ROTARY_FAST,  /**< Rotary encoder was turned anticlockwise */
    ROTARY_VERY_FAST,    /**< Rotary encoder button was pressed */
    /*@}*/
};

/*!
 * @brief Function to be called on the main event loop, receives an event data and
 * acts accordingly
 * @param [in] data Event picked by the system
 */
void process_event(event_td data, char * rx_buf,pwm_pin_TD *pwms );
/*!
 * @brief Set's up all the neccesary IO interrupts (rotary and pushbutton)
 */
void setup_IO_interrupts();
uint8_t process_rotary();
char * parse_serial(char * rx_buf, pwm_pin_TD* pwms, char * answer_buf);
/**@}*/
#ifdef __cplusplus
}
#endif
#endif /* IO_CONTROL_H */
