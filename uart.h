#include <avr/io.h>
#include <stdio.h>

void uart_init(unsigned int ubrr);
int uart_transmit(char data, FILE * file);
int uart_receive(FILE * file);
