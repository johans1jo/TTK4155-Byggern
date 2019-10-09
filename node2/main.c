#include <avr/io.h>
#include "uart.h"
#include <stdio.h>

//#define F_CPU 4915200
#define F_CPU 16000000UL
#include <util/delay.h>

#include <string.h>
#include "spi.h"
#include "MCP2515.h"
#include <avr/interrupt.h>
#include "MCP2515.h"
#include "mcp.h"
#include "can.h"

#define FOSC 16000000UL
#define BAUD 9600
//#define UBRR (FOSC/(16*BAUD))-1 //103. Riktig for U2Xn=0
#define UBRR 103

int main(void){
	//printf("Main start\r\n");
	uart_init(UBRR);

	printf("\r\n\r\n\r\nNy greie:\r\n");


	can_init(); // Denne initierer mcp, som initierer spi.
	printf("hei3\r\n");
	mcp_set_mode(MODE_NORMAL);

	printf("hei2\r\n");

	// Interruptgreier
	//mcp_bit_modify(MCP_CANINTE, 0b11111111, 0b1); // Skrur på receive0-interrupt. Skrur av alt annet.
	mcp_bit_modify(MCP_CANINTE, 0b11111111, 0b11111111); // Skrur på receive0-interrupt. Skrur av alt annet.

	/*
	GICR |= (1 << INT0); // Skrur på INT0-interrupt
	MCUCR |= (1 << ISC01); // Setter interrupts til å funke på fallende kant
	MCUCR &= ~(1 << ISC00); // ...
	DDRD &=  ~(1 << PIND2);
	*/
	printf("hei1\r\n");

	EIMSK |= (1 << INT0);
	//EICRA - fallende kant

	printf("før sei\r\n");
	//GIFR = 0;
	sei(); // Skrur på interrupts globalt
	printf("etter sei\r\n");

/*
	// Sender melding
	message_t message = {
		1, // Id
		5, // Lengde
		"heiiii" // Data. Maks åtte byte
	};
	can_send(&message); // Sender melding

	printf("har sendt melding\r\n");
	*/

	while(1){
		printf("w");
		_delay_ms(1000);
	}

	return 0;
}

ISR(INT0_vect) {
	//can_interrupt();
	printf("INT0\r\n");
	message_t receive = can_receive(); // Mottar melding
	printf("Heisann sveisann, vi har fått ei melding.\r\n");
	printf("Id: %d \r\n", receive.id);
	printf("Lengde: %d \r\n", receive.length);
	printf("Melding: %s \r\n\r\n", receive.data);
}
ISR(SPI_STC_vect) {
	printf("\r\nSPI_STC_vect\r\n");
}

ISR(BADISR_vect) {
	printf("b\r\n");
}
