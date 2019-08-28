#include <avr/io.h>
#include "uart.h"


void main( void )
{
    uart_Init ( MYUBRR );
    while (1)
    {
        uart_Transmit ('a');
    }
} 
