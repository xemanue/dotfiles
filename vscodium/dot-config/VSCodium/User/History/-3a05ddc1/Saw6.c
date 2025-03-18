/* 
 *  Copyright (C) GranaSAT - All Rights Reserved
 *  Unauthorized copying of this file, via any medium is strictly prohibited
 *  Proprietary and confidential
 *  Written by Luis Sanchez <luissanv@ugr.es>, May 2018
 */

#include "pwm_gen.h"

/**
* @details Sets CTCs mode with TOP at 24, with 8 clock prescaler.
* Found in <a href="http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-2549-8-bit-AVR-Microcontroller-ATmega640-1280-1281-2560-2561_datasheet.pdf#page=126">ATmega2560's datasheet</a>
*/
void setup_pwm_interrupt(){
    // Set timer0 interrupt at 40 kHz
    cli(); // Stop interrupts

    TCCR2A = 0; // Set entire TCCR0A register to 0
    TCCR2B = 0; // Same for TCCR0B
    TCNT2 = 0; // Initialize counter value to 0
    OCR2A =96; // Set compare match register to 40 khz increments
    TCCR2A |= (1 << WGM21); // Turn on CTC mode
    TCCR2B |= (1 << CS21); // Set CS01 bit to 8 prescaler
    TIMSK2 |= (1 << OCIE2A);// Enable timer compare interrupt

    #ifdef DEBUG_INTERRUPT
        DDRB |= _BV(7);
        TCCR2A |= (1 << COM2A0);
    #endif

    sei(); // Allow interrupts
}

void start_clock(){
    TIMSK2 |= (1 << OCIE2A); // Enable timer compare interrupt
}

void stop_clock(){
    TIMSK2 &= ~(1 << OCIE2A); // Disable timer compare interrupt
}

/**
 * @details Goes through the PWM pins vector and checks if the number of cycles
 * passed is equal to the max time on the PWM or the repeat cycle
 */
void pwm_cycle(pwm_pin_TD * pwm_pins){
    uint8_t i;
    for (i = 0; i < PWM_PINS; i++){
        switch (pwm_pins[i].en){
            case 0:
                if (pwm_pins[i].cnt >= pwm_pins[i].cycles_total ){
                    if(pwm_pins[i].cycles_on != 0){
                        turn_on(pwm_pins[i].port, pwm_pins[i].pin);
                    }

                    pwm_pins[i].cnt = 0; // Reset counter
                }

                else {
                    if (pwm_pins[i].cnt == pwm_pins[i].cycles_on){
                        turn_off(pwm_pins[i].port, pwm_pins[i].pin);
                    }
                }

                pwm_pins[i].cnt++; // Update counter
                break;
            case 1:
                turn_on(pwm_pins[i].port, pwm_pins[i].pin);
                break;
            case 2:
                turn_off(pwm_pins[i].port, pwm_pins[i].pin);
                break;
            default:
                break;
        }
    }
}
