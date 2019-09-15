#include <avr/io.h>
#include "uart.h"
#include "joystick.h"

#define F_CPU 4915200
#include <util/delay.h>



#define FOSC 4915200// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


void main( void ){
    uart_init ( MYUBRR );
    adc_init();
    while (1){
        joy_read_x();
        printf("%d \n\r", x_pos);
        _delay_ms(500);
    }
}
