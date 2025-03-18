/*
 *  Copyright (C) GranaSAT - All Rights Reserved
 *  Unauthorized copying of this file, via any medium is strictly prohibited
 *  Proprietary and confidential
 *  Written by Luis Sanchez <luissanv@ugr.es>, May 2018
 */

/**
 * @file
 * @defgroup lifo_memory
 * @code #include <lifo_mem.h> @endcode
 *
 * @brief Basic routines for the instatiation and control of a ring buffer
 * memory
 *
 * @details Due to the <pwm_gen.h> generation of PWM signals, very few clock
 * cycles are available for the rest of the system (~30%). Therefore,
 * interrupts will not handle all the display and IO routines. These will
 * instead be allocated in a ring buffer memory for a "non-interruptive" main
 * loop to act accordingly.
 */

#ifndef LIFO_MEM_H
#define LIFO_MEM_H

#include "config.h"
#include <inttypes.h>

#ifndef LIFO_MAX_SIZE
    #define LIFO_MAX_SIZE 50
#endif

// Apparently, if you use a C library, C++ compiles it using name mangling
// This prevents it
#ifdef __cplusplus
    extern "C" {
#endif

/*******************************************************************************
 * @defgroup Structs
 * @ingroup lifo_memory
 */

/** @{ */

/**
 * @brief Structure containing a specific event data
 */
typedef struct{
  uint8_t event_enum; /**< Event to be precessed */
  char * parameter; /**< Parameter, if any, to be passed to the event */
  uint8_t parameter2; /**< 2nd parameter, if any, to be passed to the event */
} event_td;

/**
 * @brief Structure containing the lifo memory
 */
typedef struct{
    event_td buf[LIFO_MAX_SIZE]; /**< Memory allocation */
    uint16_t wrt_ptr ; /**< Write pointer */
    uint16_t rd_ptr ; /**< Read pointer */
} lifo_mem;

/** @} ************************************************************************/

/*******************************************************************************
 * @defgroup Functions
 * @ingroup lifo_memory
 */

/** @{ */

/**
* @brief Checks whether the LIFO memory is empty or not
* @param [in] lifo_mem Pointer to the LIFO memory structure
* @returns 1 if memory is empty, 0 otherwise
*/
uint8_t is_lifo_empty(lifo_mem *mem);

/**
* @brief Checks whether the LIFO memory is full or not
* @param [in] mem pointer to the LIFO memory structure
* @returns 1 if memory is full 0 otherwise
*/
uint8_t is_lifo_full(lifo_mem *mem);

/**
* @brief Retrieves the next event from memory
* @param [in] lifo_mem Pointer to the LIFO memory structure
* @param [out] data Event retrieved from memory
* @returns 1 if operation was succesful, 0 otherwise
*/
uint8_t lifo_pop(lifo_mem *mem, event_td *data);

/**
* @brief Pushes data into the memory
* @param [in] lifo_mem Pointer to the LIFO memory structure
* @param [in] data Event to be stored in memory
* @returns 1 if operation was succesful, 0 otherwise
*/
uint8_t lifo_push(lifo_mem * mem, event_td data);

/** @} ************************************************************************/

#ifdef __cplusplus
}
#endif

#endif
