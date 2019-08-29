#include <avr/io.h>
#include <stdio.h>

void uart_Init( unsigned int ubrr );
int uart_Transmit(char data, FILE * file);
int uart_Receive( FILE * file );
