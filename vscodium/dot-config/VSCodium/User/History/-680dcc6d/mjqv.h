/*
 *  Copyright (C) GranaSAT - All Rights Reserved
 *  Unauthorized copying of this file, via any medium is strictly prohibited
 *  Proprietary and confidential
 *  Written by Luis Sanchez <luissanv@ugr.es>, August 2018
 */

/**
 * @file
 * @defgroup uart_control
 * @code #include <uart_control.h> @endcode
 *
 * @brief Basic functions to communicate using the UART
 */

#ifndef UART_CONTROL_H
#define UART_CONTROL_H

#include <Arduino.h>
#include <inttypes.h>
#include "config.h"

// Apparently, if you use a C library, C++ compiles it using name mangling
// This prevents it
#ifdef __cplusplus
    extern "C" {
#endif

/*******************************************************************************
 * @defgroup Functions
 * @ingroup uart_control
 */

/** @{ */

/**
 * @brief Inizializes the necessary registers to use the UART
 */
void uart_init (void);

/**
 * @brief Sends a character through the serial port
 * 
 * @param data Character to send
 */
void uart_putc(unsigned char data);

/**
 * @brief Gets a character received from the serial port
 * 
 * @return unsigned char Character received
 */
unsigned char uart_getc(void);

/**
 * @brief Sends a string through the serial port
 * 
 * @param data String to send
 */
void uart_puts(char * s);

/**
 * @brief Reads the UART receiver
 * 
 * @return char Character read
 */
inline char read_uart_rx(){
    return UDR0;
} 

/** @} ************************************************************************/

#ifdef __cplusplus
    }
#endif

#endif /* UART_CONTROL_H */