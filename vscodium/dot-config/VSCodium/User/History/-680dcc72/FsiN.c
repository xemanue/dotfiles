#include "uart_control.h"

#define BAUD 57600 // Define baud
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1) // Set baud rate value for UBRR

void uart_init (void){
    cli();

    UBRR0 = BAUDRATE; // Set baud rate
    UCSR0B|= (1<<TXEN0) | (1<<RXEN0) | (1<<RXCIE0); // Enable receiver and transmitter
    UCSR0C|= (1<<UCSZ00) | (1<<UCSZ01); // 8bit data format

    sei();
}

void uart_putc(unsigned char data){
    while (!(UCSR0A & (1<<UDRE0))); // Wait while register is empty
    UDR0 = data; // Load data in the register
}

unsigned char uart_getc(void){
    while(!(UCSR0A) & (1<<RXC0)); // Wait while data is being received

    return UDR0; // Return 8-bit data
}

void uart_puts(char * s){
    while(*s != '\0'){
        uart_putc(*s);
        s++;
    }
}
