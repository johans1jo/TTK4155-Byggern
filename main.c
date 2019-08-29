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
        if (uart_Receive()) {
          unsigned char hei = uart_Receive();
          uart_Transmit ('o');
          uart_Transmit ('k');
          uart_Transmit (hei);
        }
    }
}
