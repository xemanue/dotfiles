/*
 *  Copyright (C) GranaSAT - All Rights Reserved
 *  Unauthorized copying of this file, via any medium is strictly prohibited
 *  Proprietary and confidential
 *  Written by Luis Sanchez <luissanv@ugr.es>, May 2018
 */

 /**
 * @file
 * @defgroup virtual_PWM
 * @code #include <virtual_PWM.h> @endcode
 *
 * @brief Calculations and management for easy-to-use interface to pwm_gen.h
 */

#ifndef VIRTUAL_PWM_H
#define VIRTUAL_PWM_H

#include "config.h"
#include <Arduino.h>
#include "pwm_gen.h"

// Apparently, if you use a C library, C++ compiles it using name mangling
// This prevents it
#ifdef __cplusplus
    extern "C" {
#endif

/*******************************************************************************
 * @defgroup Functions
 * @ingroup virtual_PWM
 */

/** @{ */

/**
* @brief Set the frequency and duty cycle of a particular pin
* @param [in] pins Vector containing the PWM pins
* @param [in] pin Pin to be modified
* @param [in] freq Frequency (Hz) to be set (0 - 400 Hz)
* @param [in] duty_cycle Duty cycle (%) to be set (0 - 100)
*
* @return 1 if operation was successful
*/
int configure_pwm_pin(pwm_pin_TD * pins, uint8_t pin, uint32_t freq, uint32_t duty_cycle);

/**
* @brief Set the phase of a particular pin
* @param [in] pins Vector containing the PWM pins
* @param [in] pin Pin to be modified
* @param [in] phase Phase to be set
*/
void configure_pwm_phase(pwm_pin_TD * pins, uint8_t pin, int16_t phase);

/**
* @brief Intializes every pin
*
* @param [in] pins vector containing every PWM pin's structure
*/
void initialize_all_pins(pwm_pin_TD * pwms);

/**
 * @brief Enables PWM pin if it's currently disabled, and viceversa
 * 
 * @param pins 
 * @param pin 
 */
void toggle_pwm_pin_enable(pwm_pin_TD * pins, uint8_t pin);
void pwm_pin_enable(pwm_pin_TD * pins, uint8_t pin, uint8_t en);
void sync_pwms(pwm_pin_TD * pins);
void pin_config(pwm_pin_TD *pins, uint8_t pin, uint8_t state);

/** @} ************************************************************************/

#ifdef __cplusplus
    }
#endif

#endif /* VIRTUAL_PWM */