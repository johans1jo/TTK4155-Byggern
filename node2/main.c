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
	uart_init(UBRR);
	printf("\r\n\r\nstart\r\n");

	can_init(); // Denne initierer mcp, som initierer spi.
	mcp_set_mode(MODE_NORMAL);

	// Interruptgreier
	mcp_bit_modify(MCP_CANINTE, 0b11111111, 0b1); // Skrur på receive0-interrupt. Skrur av alt annet.
	//mcp_bit_modify(MCP_CANINTE, 0b11111111, 0b11111111); // Skrur på receive0-interrupt. Skrur av alt annet.

	/* fra node1
	GICR |= (1 << INT0); // Skrur på INT0-interrupt
	MCUCR |= (1 << ISC01); // Setter interrupts til å funke på fallende kant
	MCUCR &= ~(1 << ISC00); // ...
	DDRD &=  ~(1 << PIND2);
	*/

	EIMSK |= (1 << INT3);
	DDRB &= ~(1 << INT3);
	//EICRA bør settes til å svare på fallende kant
	EICRA |= (1 << ISC31);
	EICRA &= ~(1 << ISC30);

	//printf("før sei\r\n");
	sei(); // Skrur på interrupts globalt
	//printf("etter sei\r\n");

	// Sender melding
	message_t message = {
		0, // Id
		3, // Lengde
		"max" // Data. Maks åtte byte
	};
	can_send(&message); // Sender melding

	printf("har sendt melding\r\n");

	while(1){
		//printf("hei\r\n");
		_delay_ms(1000);
	}

	return 0;
}

ISR(INT3_vect) {
	message_t receive = can_receive(); // Mottar melding
	if (receive.id == 10) {
		//x
		printf("x: %d\r\n", receive.data[0]);
	} else if (receive.id == 11) {
		//y
		printf("y: %d\r\n\r\n", receive.data[0]);
	} else {
		if (receive.length > 8) {
			printf("Kaos. Meldingslengde: %d\r\n", receive.length);
		} else {
			printf("Heisann sveisann, vi har fått ei melding.\r\n");
			printf("Id: %d \r\n", receive.id);
			printf("Lengde: %d \r\n", receive.length);
			printf("Melding: %s \r\n\r\n", receive.data);
		}
	}
	// Resetter interrupt for motta-buffer0
	mcp_bit_modify(MCP_CANINTF, 0b1, 0);
}

ISR(SPI_STC_vect) {
	//printf("\r\nSPI_STC_vect\r\n");
}

ISR(BADISR_vect) {
	printf("\r\nBADISR_vect\r\n");
}
