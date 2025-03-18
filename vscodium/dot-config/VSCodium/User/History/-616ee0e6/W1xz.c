/* 
 * Copyright (C) GranaSAT - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Luis Sanchez <luissanv@ugr.es>, May 2018
 * Modified by Prof. Andrés Roldán <amroldan@ugr.es>, Dic 2019
 */
#include "virtual_PWM.h"
#include "uart_control.h"

/**
 * @details Experimentally got 106 counter value to obtain 400 Hz. Since
 * frequency changes linearly with counter value, we can use the cross product
 * to calculate the desired counter value
 */
int configure_pwm_pin(pwm_pin_TD *pins, uint8_t pin, uint32_t freq,
                      uint32_t duty_cycle){
    if (freq > 4000){
        freq = 4000;
    }
    
    if (duty_cycle > 100){
        duty_cycle = 100;
    }
    
    else {
        uint32_t per = 200000U/freq;
        uint32_t ton = per*duty_cycle/100U;
        
        pins[pin].cycles_total = per;
        pins[pin].cycles_on = ton;
        pins[pin].frq = (uint16_t) freq;
        pins[pin].dty = (uint16_t) duty_cycle;
        
        pin_config(pins, pin, 1);
        
        return 1;
    }
}

/**
 * @details Sets the phase value and applies the changes to the counter
 */
void configure_pwm_phase(pwm_pin_TD *pins, uint8_t pin, int16_t phase){
    pins[pin].cnt = pins[pin].cnt + pins[pin].cycles_total*phase/100
                                    - pins[pin].cycles_total*pins[pin].phase/100;
    pins[pin].phase = phase;
}

/**
 * @note Needs to be modified if more than 8 pins are used
 */
void initialize_all_pins(pwm_pin_TD *pwms){
    pwms[0].port = &(PWM_PORT_0);
    pwms[0].port_config = &(PWM_PORT_CONF_0);
    pwms[0].pin = PWM_PIN_0;

    pwms[1].port = &(PWM_PORT_1);
    pwms[1].port_config = &(PWM_PORT_CONF_1);
    pwms[1].pin = PWM_PIN_1;

    pwms[2].port = &(PWM_PORT_2);
    pwms[2].port_config = &(PWM_PORT_CONF_2);
    pwms[2].pin = PWM_PIN_2;

    pwms[3].port = &(PWM_PORT_3);
    pwms[3].port_config = &(PWM_PORT_CONF_3);
    pwms[3].pin = PWM_PIN_3;

    pwms[4].port = &(PWM_PORT_4);
    pwms[4].port_config = &(PWM_PORT_CONF_4);
    pwms[4].pin = PWM_PIN_4;

    pwms[5].port = &(PWM_PORT_5);
    pwms[5].port_config = &(PWM_PORT_CONF_5);
    pwms[5].pin = PWM_PIN_5;

    pwms[6].port = &(PWM_PORT_6);
    pwms[6].port_config = &(PWM_PORT_CONF_6);
    pwms[6].pin = PWM_PIN_6;

    pwms[7].port = &(PWM_PORT_7);
    pwms[7].port_config = &(PWM_PORT_CONF_7);
    pwms[7].pin = PWM_PIN_7;
}

void pwm_pin_enable(pwm_pin_TD *pins, uint8_t pin, uint8_t en){
    pins[pin].en = en; 
}

void toggle_pwm_pin_enable(pwm_pin_TD *pins, uint8_t pin){
    if (pins[pin].en){
        pins[pin].en = 0;
    }

    else {
        pins[pin].en = 1;
    }
}

/**
 * @details Go through all the pins, set their counter to 0 and then substract
 * the phase
 */
void sync_pwms(pwm_pin_TD *pins){
    uint8_t i;
    stop_clock();
    
    for (uint8_t i = 0; i < PWM_PINS; i++){
        pins[i].cnt = 0; 
        pins[i].cnt = pins[i].cnt + pins[i].cycles_total * pins[i].phase / 100;
    }
    
    start_clock();
}

void pin_config(pwm_pin_TD *pins, uint8_t pin, uint8_t state){
    if (state){
        *(pins[pin].port_config) |= _BV(pins[pin].pin);
    }

    else {
        *(pins[pin].port_config) &= (0xFF & (~(_BV(pins[pin].pin))));
    }
}


