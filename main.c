#include <avr/io.h>
#include "uart.h"

#define FOSC 4915200// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


void main( void )
{
    uart_Init ( MYUBRR );
    while (1)
    {
        uart_Transmit ('a');
    }
}
