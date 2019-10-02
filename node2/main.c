#include <avr/io.h>
#include "uart.h"
#include <stdio.h>

#define F_CPU 4915200
#include <util/delay.h>

#include <string.h>
#include "spi.h"
#include "MCP2515.h"
#include <avr/interrupt.h>
#include "MCP2515.h"
#include "mcp.h"
#include "can.h"

#define FOSC 4915200// Clock Speed
#define BAUD 9600
#define UBRR FOSC/16/BAUD-1

volatile uint8_t test = 0;

int main(void){
	//printf("Main start\r\n");
	uart_init(UBRR);
	can_init(); // Denne initierer mcp, som initierer spi.
	mcp_set_mode(MODE_NORMAL);

	// Interruptgreier
	mcp_bit_modify(MCP_CANINTE, 0b11111111, 0b1); // Skrur på receive0-interrupt. Skrur av alt annet.
	GICR |= (1 << INT0); // Skrur på INT0-interrupt
	MCUCR |= (1 << ISC01); // Setter interrupts til å funke på fallende kant
	MCUCR &= ~(1 << ISC00); // ...
	DDRD &=  ~(1 << PIND2);

	printf("før sei\r\n");
	//GIFR = 0;
	sei(); // Skrur på interrupts globalt
	printf("etter sei\r\n");

	// Sender melding
	message_t message = {
		1, // Id
		5, // Lengde
		"heiiii" // Data. Maks åtte byte
	};
	can_send(&message); // Sender melding

	printf("har sendt melding\r\n");

	while(1){
		printf("w");
		_delay_ms(1000);
	}

	return 0;
}

ISR(INT0_vect) {
	//can_interrupt();
	message_t receive = can_receive(); // Mottar melding
	printf("Heisann sveisann, vi har fått ei melding.\r\n");
	printf("Id: %d \r\n", receive.id);
	printf("Lengde: %d \r\n", receive.length);
	printf("Melding: %s \r\n\r\n", receive.data);
}
ISR(SPI_STC_vect) {
	//printf("\r\nSPI_STC_vect\r\n");
}

ISR(BADISR_vect) {
	printf("b");
}
