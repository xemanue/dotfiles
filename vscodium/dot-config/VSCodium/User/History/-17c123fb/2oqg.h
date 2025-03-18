/* 
 *  Copyright (C) GranaSAT - All Rights Reserved
 *  Unauthorized copying of this file, via any medium is strictly prohibited
 *  Proprietary and confidential
 *  Written by Luis Sanchez <luissanv@ugr.es>, August 2018
 */

 /**
 * @file
 * @defgroup eeprom_control
 * @code #include <eeprom_control.h> @endcode
 *
 * @brief Basic structs and functions to transfer data to and from memory
 */

#ifndef EEPROM_CONTROL_H
#define EEPROM_CONTROL_H

#include "config.h"
#include <Arduino.h>
#include <inttypes.h>
#include <avr/eeprom.h>

// Apparently, if you use a C library, C++ compiles it using name mangling
// This prevents it
#ifdef __cplusplus
    extern "C" {
#endif

/*******************************************************************************
 * @defgroup Structs
 * @ingroup eeprom_control
 */

/** @{ */

 /**
 * @brief Data structure to represent a PWM in memory
 */
typedef struct pwm_to_eeprom {
    uint16_t freq; /**< Frequency */
    uint8_t dty; /**< Duty cicle */
    uint8_t en; /**< Enabled */
    uint8_t phs; /**< Phase */

    char nombre[12]; /**< Name */
} pwm_to_eeprom_t;

/**
 * @brief Older version of pwm_to_eeprom
 * @sa pwm_to_eeprom
 */
typedef struct pwm_reducida {
    uint16_t freq:9;
    uint8_t freq_decimal:4;
    int8_t dty:7;
    uint8_t en:2;
    uint8_t phs;

    char nombre[12];
}; 

/**
 * @brief Data structure to store a specific car's PWM settings
 */
typedef struct coche {
    pwm_to_eeprom_t senialesPwm[8]; /**< PWMs for the specific model */
    char nombreCoche[12]; /**< Car name */
    uint8_t vectorized[PWM_PINS*sizeof(pwm_to_eeprom_t)]; /**< Array that helps
                                                          navigate the struct */
};

/**
 * @brief Structure used to transfer data to and from memory
 */
union eeprom_bridge {
    pwm_to_eeprom_t pwm_data[PWM_PINS];
    char nombre[12]; 
    uint8_t vectorized[PWM_PINS*sizeof(pwm_to_eeprom_t)];
};

/** @} ************************************************************************/

/*******************************************************************************
 * @defgroup Functions
 * @ingroup eeprom_control
 */

/** @{ */

/**
 * @brief Writes data to a position in memory
 * 
 * @param[in] position Position where data will be written
 * @param[in] data Data to be written
 */
void eeprom_write_to(uint16_t position, uint8_t data);

/**
 * @brief Reads data from a position in memory
 * 
 * @param[in] position Position where data will be read from
 * @return uint8_t Byte read
 */
uint8_t eeprom_read_from(uint16_t position);

/**
 * @brief Writes given PWMs to memory
 * 
 * @param[out] data PWM to be written
 * @param[in] mem_pos Position where PWM will be written to
 */
void eeprom_save_pwms(pwm_to_eeprom_t * data, uint8_t mem_pos);

/**
 * @brief Reads PWMs from memory
 * 
 * @param[out] data Structure which read PWM will be output to
 * @param[in] mem_pos Memory position where PWM will be read from
 * @return uint8_t TODO
 */
uint8_t eeprom_load_pwms(pwm_to_eeprom_t *data, uint8_t mem_pos);

/**
 * @brief Initialize a memory position
 * 
 * @param[out] data Structure which initialized PWM will be output to
 * @param[in] mem_pos Position where PWM will be written to
 * @return uint8_t TODO
 */
uint8_t eeprom_init(pwm_to_eeprom_t *data,  uint8_t mem_pos);

/**
 * @brief Gets the name of the car from memory
 * 
 * @param[out] nombre Which the name will be output to
 * @param[in] posicion Memory position where the car name will be read from
 */
void obtenerNombreCoche(char *nombre, uint8_t posicion);

/**
 * @brief Writes the name of a car to memory
 * 
 * @param[in] nombreCoche Name to be written
 * @param[in] posicion Where the name will be written
 */
void guardarNombreCoche(char *nombreCoche, uint8_t posicion);

/**
 * @brief Gets number of cars stored in memory
 * 
 * @return uint8_t Number of cars stored in memory
 */
uint8_t obtenerNumCoches();

/** @} ************************************************************************/

#ifdef __cplusplus
    }
#endif

#endif /* EEPROM_CONTROL_H */