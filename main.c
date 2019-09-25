#include <avr/io.h>
#include "uart.h"
#include "joystick.h"
#include <stdio.h>

#define F_CPU 4915200
#include <util/delay.h>

#include "oled.h"
#include <string.h>
#include "menu.h"
#include "spi.h"
#include "MCP2515.h"
#include <avr/interrupt.h>
#include "sram.h"
#include "draw.h"
#include "MCP2515.h"
#include "mcp.h"
#include "can.h"

//#define sei()
//#define ISR(int0_vect)

#define FOSC 4915200// Clock Speed
#define BAUD 9600
#define UBRR FOSC/16/BAUD-1

// INT0-interruptfunksjon
ISR(INT0_vect) {
	printf("interrupt\r\n");
}

int main(void){
	uart_init(UBRR);

	GICR |= (1 << INT0);
	MCUCR |= (1 << ISC01);
	MCUCR &= ~(1 << ISC00);

	sei();

	while(1) {
	};

	return 0;
}
