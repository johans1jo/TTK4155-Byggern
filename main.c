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

#define FOSC 4915200// Clock Speed
#define BAUD 9600
#define UBRR FOSC/16/BAUD-1

// INT0-interruptfunksjon
ISR(INT0_vect) {
	can_interrupt();
}

int main(void){
	uart_init(UBRR);
	can_init(); // Denne initierer mcp, som initierer spi.
	mcp_set_mode(MODE_LOOPBACK);

	message_t message = {
		1, // Id
		3, // Lengde
		"hei" // Data. Maks åtte byte
	};

	can_send(&message); // Sender melding

	//Delay?

	message_t receive = can_receive(); // Mottar melding
	printf("Heisann sveisann, vi har fått ei melding.\r\n");
	printf("Id: %d \r\n", receive.id);
	printf("Lengde: %d \r\n", receive.length);
	printf("Melding: %s \r\n\r\n", receive.data);


	/* Interruptgreier. Trengs ikke før lab 6
	GICR |= (1 << INT0); // Skrur på INT0-interrupt
	MCUCR |= (1 << ISC01); // Setter interrupts til å funke på fallende kant
	MCUCR &= ~(1 << ISC00); // ...
	sei(); // Skrur på interrupts globalt
	*/

	return 0;
}
