/* 
 *  Copyright (C) GranaSAT - All Rights Reserved
 *  Unauthorized copying of this file, via any medium is strictly prohibited
 *  Proprietary and confidential
 *  Written by Luis Sanchez <luissanv@ugr.es>, August 2018
 */

#ifndef EEPROM_CONTROL_H
#define EEPROM_CONTROL_H

#include "config.h"
#include <Arduino.h>
#include <inttypes.h>
#include <avr/eeprom.h>

// Apparently, if you use a C library, C++ compiles it using name mangling. This prevents it
#ifdef __cplusplus
    extern "C" {
#endif

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
    uint8_t vectorized[PWM_PINS*sizeof(pwm_to_eeprom_t)]; /**< Array that helps navigate the struct */
};

/**
 * @brief Structured used to transfer data to and from memory
 */
union eeprom_bridge {
    pwm_to_eeprom_t pwm_data[PWM_PINS];
    char nombre[12]; 
    uint8_t vectorized[PWM_PINS*sizeof(pwm_to_eeprom_t)];
};

/**
 * @brief Writes data to a position in memory
 * 
 * @param position Position where data will be written
 * @param data Data to be written
 */
void eeprom_write_to(uint16_t position, uint8_t data);

/**
 * @brief Reads data from a position in memory
 * 
 * @param position Position where data will be read from
 * @return uint8_t Byte read
 */
uint8_t eeprom_read_from(uint16_t position);

/**
 * @brief Writes given PWMs to memory
 * 
 * @param data PWMs to be written
 * @param mem_pos Position where PWMs will be written to
 */
void eeprom_save_pwms(pwm_to_eeprom_t * data, uint8_t mem_pos);

/**
 * @brief Reads PWMs from memory
 * 
 * @param data Structure which read PWMs will be output to
 * @param mem_pos Memory position where PWMs will be read from
 * @return uint8_t TODO
 */
uint8_t eeprom_load_pwms(pwm_to_eeprom_t *data, uint8_t mem_pos);

/**
 * @brief Initialize a memory position
 * 
 * @param data PWMs to be written
 * @param mem_pos Position where PWMs will be written to
 * @return uint8_t TODO
 */
uint8_t eeprom_init(pwm_to_eeprom_t *data,  uint8_t mem_pos);

/**
 * @brief Gets the name of the car from memory
 * 
 * @param nombre Which the name will be output to
 * @param posicion Memory position where the car name will be read from
 */
void obtenerNombreCoche(char * nombre, uint8_t posicion);

/**
 * @brief Writes the name of a car to memory
 * 
 * @param nombreCoche Name to be written
 * @param posicion Where the name will be written
 */
void guardarNombreCoche(char * nombreCoche, uint8_t posicion);

/**
 * @brief Gets number of cars stored in memory
 * 
 * @return uint8_t Number of cars stored in memory
 */
uint8_t obtenerNumCoches();


#ifdef __cplusplus
    }
#endif

#endif /* EEPROM_CONTROL_H */
