/* 
 *  Copyright (C) GranaSAT - All Rights Reserved
 *  Unauthorized copying of this file, via any medium is strictly prohibited
 *  Proprietary and confidential
 *  Written by Luis Sanchez <luissanv@ugr.es>, August 2018
 */

/**
 * @file
 * @defgroup IO_control <IO_control.h>
 * @code #include <IO_control.h> @endcode
 *
 * @brief Short module to setup and process IO events
 * 
 * Sets up the neccesary interrupts for the IO lines (roraty and push-button),
 * as well as the required functions to process such events
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

// Apparently, if you use a C library, C++ compiles it using name mangling
// This prevents it
#ifdef __cplusplus
    extern "C" {
#endif

#define DIR_CW 0x10 // Clockwise
#define DIR_CCW 0x20 // Counterclockwise
#define DIR_NONE 0x0

/**
 * @brief Type of events
 */
enum EventType {
    MOVEMENT_UP = 0, /**< Rotary encoder was turned clockwise */
    MOVEMENT_DOWN, /**< Rotary encoder was turned counterclockwise */
    BUTTON_PUSH, /**< Rotary encoder button was pressed */
    QUICK_BUTTON_PUSH, /**< Rotary encoder button was pressed fast */
    UART_RX /**< Message received from UART */
};

/**
 * @brief Types of velocity for the rotary encoder
 */
enum RotaryVelocity {
    ROTARY_SLOW = 0,
    ROTARY_FAST,
    ROTARY_VERY_FAST
};

/**
 * @brief Receives an event and acts accordingly
 * @param[in] data Event to be acted upon
 */
void process_event(event_td data, char * rx_buf,pwm_pin_TD *pwms );

/**
 * @brief Sets up the neccesary IO interrupts for the rotary encoder and the
 * push-button
 */
void setup_IO_interrupts();


uint8_t process_rotary();


char * parse_serial(char * rx_buf, pwm_pin_TD* pwms, char * answer_buf);


#ifdef __cplusplus
    }
#endif

#endif /* IO_CONTROL_H */