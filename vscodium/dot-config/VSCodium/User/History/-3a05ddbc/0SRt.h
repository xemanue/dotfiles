/*
 *  Copyright (C) GranaSAT - All Rights Reserved
 *  Unauthorized copying of this file, via any medium is strictly prohibited
 *  Proprietary and confidential
 *  Written by Luis Sanchez <luissanv@ugr.es>, May 2018
 */

/**
 * @file
 * @defgroup pwm_gen
 * @code #include <pwm_gen.h> @endcode
 *
 * @brief Basic routines to manage the control timer and generating PWMs
 */

#ifndef PWM_GEN_H
#define PWM_GEN_H

#include "config.h"
#include <Arduino.h>

#ifndef PWM_PINS
    #define PWM_PINS 8
#endif

// Apparently, if you use a C library, C++ compiles it using name mangling
// This prevents it
#ifdef __cplusplus
    extern "C" {
#endif

/*******************************************************************************
 * @defgroup Structs
 * @ingroup pwm_gen
 */

/** @{ */

/**
 * @brief Structure to represent a PWM pin 
 */
typedef struct pwm_pin {
    uint8_t * port; /**< GPIO port in the ATMEGA2560 */
    uint8_t * port_config; /**< GPIO configuration register in the ATMEGA2560 */
    uint8_t pin; /**< GPIO port's bit in the ATMEGA2560 */
    uint8_t en; /**< Is the channel enabled? */
    uint32_t cycles_on; /**< Number of interrupt cycles in which the pin shall be HIGH */
    uint32_t cycles_total; /**< Number of interrupt cycles that constitute a period */
    uint32_t cnt; /**< Interrupt cycles counter */
    uint16_t dty; /**< Intended duty cycle for the pin */
    uint16_t frq; /**< Intended frequency for the pin */
    int16_t phase; /**< Intended phase for the pin */
    // char nombre[12];
} pwm_pin_TD;

/** @} ************************************************************************/

/*******************************************************************************
 * @defgroup Functions
 * @ingroup pwm_gen
 */

/** @{ */

/**
* @brief This functions set up internal PWM clock 0 to generate an interrupt at a 40 kHz firing rate
*/
void setup_pwm_interrupt();

/**
* @brief function to be called on each interrupt cycle, handles the ON/OFF of the PWM pins
* @param [in] pwm_pins vector containing all the PWM pins structures
*/
void pwm_cycle(pwm_pin_TD * pwm_pins);

/**
* @brief Turns off pin (quickly)
* @param [in] port pointer to the GPIO addres
* @param [in] pin bit in port to be turned off
*/


void start_clock();
void stop_clock();
/**
* @brief Turns on pin (quickly)
* @param [in] port pointer to the GPIO addres
* @param [in] pin bit in port to be turned on
*/
void inline turn_on(uint8_t *port, uint8_t pin){
    *port |= _BV(pin); 
}

#ifdef __cplusplus
    }
#endif

#endif /* PWM_GEN_H */
