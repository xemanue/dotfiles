#include "eeprom_control.h"
#include "uart_control.h"

char eedata[0xFF] EEMEM = { };
char dbuf[50];
char ayuda[12];
uint8_t numCoches = 0;
uint8_t TAMNOMBRE = sizeof(ayuda);
uint8_t eeprom_pwms_start_address = 0x01;
uint8_t eeprom_pwms_mem_pos = 0x04;

byte EEPROM_init_values[] = { 105,
                              21,0,10,0,0,
                              22,0,20,0,0,
                              23,0,30,0,0,
                              24,0,40,0,0,
                              25,0,50,0,0,
                              26,0,60,0,0,
                              27,0,70,0,0,
                              28,0,80,0,0,
                              21,0,11,0,0,
                              22,0,21,0,0,
                              23,0,31,0,0,
                              24,0,41,0,0,
                              25,0,51,0,0,
                              26,0,61,0,0,
                              27,0,71,0,0,
                              28,0,81,0,0,
                              21,0,12,0,0,
                              22,0,22,0,0,
                              23,0,32,0,0,
                              24,0,42,0,0,
                              25,0,52,0,0,
                              26,0,62,0,0,
                              27,0,72,0,0,
                              28,0,82,0,0,
                              21,0,13,0,0,
                              22,0,23,0,0,
                              23,0,33,0,0,
                              24,0,43,0,0,
                              25,0,53,0,0,
                              26,0,63,0,0,
                              27,0,73,0,0,
                              28,0,83,0,0 };

void eeprom_write_to(uint16_t position, uint8_t data) {
    if (data != eeprom_read_from(position)) {
        eeprom_write_byte(&eedata[position], data);
    }
}

uint8_t eeprom_read_from(uint16_t position) {
    return eeprom_read_byte(&eedata[position]);
}

void obtenerNombreCoche(char * nombre, uint8_t posicion) {
    union eeprom_bridge bridge;
    char nombreAux[12];

    for (int i = 0; i < TAMNOMBRE; i++) {
        nombreAux[i] = eeprom_read_from(i + posicion * (sizeof(bridge.vectorized) + TAMNOMBRE) + eeprom_pwms_start_address);
    }
    
    strcpy(nombre, nombreAux);
}

void guardarNombreCoche(char *nombreCoche, uint8_t posicion) {
    union eeprom_bridge bridge;

    for (int i = 0; i < TAMNOMBRE; i++){
        eeprom_write_to(i + posicion * (sizeof(bridge.vectorized) + TAMNOMBRE) + eeprom_pwms_start_address,
                        nombreCoche[i]);
    }

    if (posicion > numCoches) numCoches = posicion;
}

uint8_t obtenerNumCoches() {
    return numCoches;
}

void eeprom_save_pwms(pwm_to_eeprom_t *data, uint8_t mem_pos) {
    union eeprom_bridge bridge;

    /*
        memcpy(bridge.pwm_data, data, PWM_PINS * sizeof(pwm_to_eeprom_t));
        eeprom_write_to(mem_pos * sizeof(union eeprom_bridge) + eeprom_pwms_start_address, name );
        
        uint16_t i = 0;
        for(i = 0; i < sizeof(bridge.vectorized); i++) {
            eeprom_write_to(i + mem_pos * sizeof(bridge.vectorized) + eeprom_pwms_start_address + TAMNOMBRE,
                            bridge.vectorized[i]);
        }
    */

    memcpy(bridge.pwm_data, data, PWM_PINS * sizeof(pwm_to_eeprom_t));

    uint16_t i = 0;
    for(i = 0; i < sizeof(bridge.vectorized); i++) {
        eeprom_write_to(i + mem_pos * (sizeof(bridge.vectorized) + TAMNOMBRE) + eeprom_pwms_start_address + TAMNOMBRE,
                        bridge.vectorized[i]);
    }
}

uint8_t eeprom_load_pwms(pwm_to_eeprom_t *data,  uint8_t mem_pos) {
    union eeprom_bridge bridge;

    /*
        union eeprom_bridge {
            pwm_to_eeprom_t pwm_data[PWM_PINS];
            uint8_t vectorized[PWM_PINS * sizeof(pwm_to_eeprom_t)];
        };

        // Estoy intentando copiar el nombre del bridge
        name = eeprom_read_from(mem_pos * sizeof(union eeprom_bridge) + eeprom_pwms_start_address);
        
        uint16_t i = 0;
        for (i = 0; i < sizeof(bridge.vectorized); i++) {
            bridge.vectorized[i] = eeprom_read_from(i + mem_pos * sizeof(union eeprom_bridge) + eeprom_pwms_start_address + TAMNOMBRE);
        }
        
        memcpy(data, bridge.pwm_data, PWM_PINS * sizeof(bridge.vectorized));
    */
     
    uint16_t i = 0; 
    for(i = 0; i < sizeof(bridge.vectorized); i++) {
        bridge.vectorized[i] = eeprom_read_from(i + mem_pos * (sizeof(bridge.vectorized) + TAMNOMBRE) + eeprom_pwms_start_address + TAMNOMBRE);
    }

    memcpy(data, bridge.pwm_data, PWM_PINS * sizeof(bridge.vectorized));
}

// Si la EEPROM(0) no está inicializada, grabamos un valor por defecto de PWM
void eeprom_initialization(void) {
    for (int i = 0; i < sizeof(EEPROM_init_values); i++) {
        //eeprom_write_to(uint16_t position, uint8_t data)
        eeprom_write_to(i, EEPROM_init_values[i]);
    }
}

// Función para inicializar la EEPROM. Usa consigna 0x69 en posición 0
uint8_t eeprom_init(pwm_to_eeprom_t *data, uint8_t mem_pos) {
    uint8_t i = 0;
    if (eeprom_read_from(0x00) != 0x69 /* 105 en DEC */) {
        // Memoria virgen la primera vez
        for(i = 0; i < sizeof(union eeprom_bridge) * eeprom_pwms_mem_pos; i++) {
            eeprom_write_to(i+eeprom_pwms_start_address, 0x00);
        }

        // eeprom_write_to(0x00, 0x69);
        eeprom_initialization();
    }

    //Por ahora yo solo tengo dos coches guardados en eeprom
    numCoches = 2;
    
    //La EEPROM no está virgen y cargamos los valores almacenados en el Banco 0.
    eeprom_load_pwms(data, 0);
}
