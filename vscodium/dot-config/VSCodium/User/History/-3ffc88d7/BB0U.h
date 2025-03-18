/*
 *  Copyright (C) GranaSAT - All Rights Reserved
 *  Unauthorized copying of this file, via any medium is strictly prohibited
 *  Proprietary and confidential
 *  Written by Luis Sanchez <luissanv@ugr.es>, May 2018
 */

/**
 * @file
 * @brief Configuration defines for the whole firmware
 */

/**
 * @mainpage
 * Collection of libraries for AVR-GCC
 * @author Luis Sanchez Velasco hfegetude@gmail.com
 * @copyright (C) 2018 Luis Sanchez Velasco & The GranaSAT Group
 * @brief Control firmware for a PWM signal generator 
 * This firmware is able to make an ATmega2560 generate a PWM signal with 
 * +/- 2% duty cycle variations from 1 to 400 Hz through the selected pins.
 * It includes a LCD screen to display data and a rotary encoder controller.
 * Data can also be sent through the serial port
 * @version  Dev
 */

/*
    #define PCB_VERSION_21  // PCB verde donde los OUT1 y 2 se usan los pines del serial TX/RX0
    #define PCB_VERSION_22  // PCB negra bien con 7805
*/

#define PCB_VERSION_23  //PCB negra bien con 7805 y diodo THT soldado en patilla del 7805

#define SW_VERSION "1.21"

// #define DEBUG_ROTARY 

// V2.3 Placa negra en conectores y Arduino
#ifdef PCB_VERSION_23
    /** Number of PWM pins */
    #define PWM_PINS 8

    // PIN 4 - Pin del esquema donde va la salida correspondiente
    #define PWM_PORT_0 PORTE
    #define PWM_PORT_CONF_0 DDRE
    #define PWM_PIN_0  4

    // PIN 3
    #define PWM_PORT_1 PORTE
    #define PWM_PORT_CONF_1 DDRE
    #define PWM_PIN_1  5

    // PIN 4
    #define PWM_PORT_2 PORTG
    #define PWM_PORT_CONF_2 DDRG
    #define PWM_PIN_2  5

    // PIN 6
    #define PWM_PORT_3 PORTH
    #define PWM_PORT_CONF_3 DDRH
    #define PWM_PIN_3  3

    // PIN 7
    #define PWM_PORT_4 PORTH
    #define PWM_PORT_CONF_4 DDRH
    #define PWM_PIN_4  4
    
    // PIN 38
    #define PWM_PORT_5 PORTD
    #define PWM_PORT_CONF_5 DDRD
    #define PWM_PIN_5  7

    // PIN 8
    #define PWM_PORT_6 PORTH
    #define PWM_PORT_CONF_6 DDRH
    #define PWM_PIN_6  5

    // PIN 11
    #define PWM_PORT_7 PORTB
    #define PWM_PORT_CONF_7 DDRB
    #define PWM_PIN_7  5

    #define HW_VERSION "2.3"  // Placa negra con 7805 con diodo serie en patilla de 7805
#endif

#ifdef PCB_VERSION_22
  //V2.2  Placa Negra
  /** Number of PWM pins */
  #define PWM_PINS 8
  //pin 2   //Pin del esquema donde va la salida correspondiente
  #define PWM_PORT_0 PORTE
  #define PWM_PORT_CONF_0 DDRE
  #define PWM_PIN_0  4
  //pin 3
  #define PWM_PORT_1 PORTE
  #define PWM_PORT_CONF_1 DDRE
  #define PWM_PIN_1  5
  //pin 4
  #define PWM_PORT_2 PORTG
  #define PWM_PORT_CONF_2 DDRG
  #define PWM_PIN_2  5
  //pin 6
  #define PWM_PORT_3 PORTH
  #define PWM_PORT_CONF_3 DDRH
  #define PWM_PIN_3  3
  //pin 7
  #define PWM_PORT_4 PORTH
  #define PWM_PORT_CONF_4 DDRH
  #define PWM_PIN_4  4
  //pin 38
  #define PWM_PORT_5 PORTD
  #define PWM_PORT_CONF_5 DDRD
  #define PWM_PIN_5  7
  //pin 8
  #define PWM_PORT_6 PORTH
  #define PWM_PORT_CONF_6 DDRH
  #define PWM_PIN_6  5
  //pin 11
  #define PWM_PORT_7 PORTB
  #define PWM_PORT_CONF_7 DDRB
  #define PWM_PIN_7  5

  #define HW_VERSION "2.2"  // Placa negra con 7805

#endif


#ifdef PCB_VERSION_21
//V2.1  Placa Verde  a esta se USA mal el Pin0 y 1 que se comparten con el SERIAL de programación.
  /** Number of PWM pins */
  #define PWM_PINS 8
  //pin 0 
  #define PWM_PORT_0 PORTE
  #define PWM_PORT_CONF_0 DDRE
  #define PWM_PIN_0  0
  //pin 1
  #define PWM_PORT_1 PORTE
  #define PWM_PORT_CONF_1 DDRE
  #define PWM_PIN_1  1
  //pin 2
  #define PWM_PORT_2 PORTE
  #define PWM_PORT_CONF_2 DDRE
  #define PWM_PIN_2  4
  //pin 3
  #define PWM_PORT_3 PORTE
  #define PWM_PORT_CONF_3 DDRE
  #define PWM_PIN_3  5
  //pin 4
  #define PWM_PORT_4 PORTG
  #define PWM_PORT_CONF_4 DDRG
  #define PWM_PIN_4  5
  //pin 38
  #define PWM_PORT_5 PORTD
  #define PWM_PORT_CONF_5 DDRD
  #define PWM_PIN_5  7
  //pin 8
  #define PWM_PORT_6 PORTH
  #define PWM_PORT_CONF_6 DDRH
  #define PWM_PIN_6  5
  //pin 11
  #define PWM_PORT_7 PORTB
  #define PWM_PORT_CONF_7 DDRB
  #define PWM_PIN_7  5

  #define HW_VERSION "2.1"  // Placa verde inicial con los cambios hardware
  //Pines PWM1 llevada al PE4
  //Pines PWM2 llevada al PE5
  //Pines PWM3 llevada al PG5
  //Pines PWM4 llevada al PH3
  //Pines PWM5 llevada al PH4
  //Rotary con problema que le falta alimentación
#endif




/** Define to toggle a pin at f/2 of interrupt frequency  */
#define DEBUG_INTERRUPT

/** Define to set a pin at the start of the interrupt and clear at the end (obtain CPU usage of the interrupt)  */
#define DEBUG_INTERRUPT_USAGE 
#ifdef DEBUG_INTERRUPT_USAGE 
#define DEBUG_INTERRUPT_PORT PORTE
#define DEBUG_INTERRUPT_PIN 3
#endif

/** Size of LIFO meme */
#define LIFO_MAX_SIZE 50

/**LCD Rows */
#define LCD_ROWS


//#define DEBUG_EVENT_LOOP

#define ENCODER_A_BIT  1
#define ENCODER_A_PIN  PIND
#define ENCODER_B_BIT  3
#define ENCODER_B_PIN  PIND
#define BAN_ROTARY 100
#define VERY_FAST_ROTARY 200
#define FAST_ROTARY 400
#define SLOW_ROTARY 400
#define BUTTON_DEBOUNCING 1000
#define DOUBLE_BUTTON_TIME 1000


  
//#define HW_VERSION "2.2"  // Placa negra inicial con los cambios hardware
  //Pines PWM1 llevada al PE4
  //Pines PWM2 llevada al PE5
  //Pines PWM3 llevada al PG5
  //Pines PWM4 llevada al PH3
  //Pines PWM5 llevada al PH4

#define SCREENSAVER_TIMEOUT 30
#define BOOT_DELAY_MS 2000
