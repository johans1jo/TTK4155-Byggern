#include <stdio.h>
#include <string.h>

#define F_CPU 4915200
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "uart.h"
#include "joystick.h"
#include "oled.h"
#include "menu.h"
#include "spi.h"
#include "MCP2515.h"
#include "mcp.h"
#include "can.h"
#include "sram.h"
#include "draw.h"
#include "buttons.h"
#include "mode.h"
#include "game.h"

#define FOSC 4915200// Clock Speed
#define BAUD 9600
#define UBRR FOSC/16/BAUD-1

int main(void){
	uart_init(UBRR);
	can_init(); // Denne initierer mcp, som initierer spi.
  adc_init();
  joy_calibrate();
	sram_init();
	buttons_init();
	game_init();
	printf("hei\r\n");

	oled_init();
	oled_clear();
	draw_init();

	// Interruptgreier
	mcp_bit_modify(MCP_CANINTE, 0b11111111, 0b1); // Skrur på receive0-interrupt. Skrur av alt annet.
	GICR |= (1 << INT0); // Skrur på INT0-interrupt
	MCUCR |= (1 << ISC01); // Setter interrupts til å funke på fallende kant
	MCUCR &= ~(1 << ISC00); // ...
	DDRD &=  ~(1 << PIND2);

	//? GIFR = 0;
	sei(); // Skrur på interrupts globalt

	menu_ptr menu_main = menu_init(MAIN);
	while(1) {
		menu_start(menu_main);
	}

	printf("farvel\r\n");
	return 0;
}

ISR(INT0_vect) {
	message_t receive = can_receive(); // Mottar melding
	if (receive.id == 1) {
		printf("CAN: Mottok id 1\r\n");
	} else {
		printf("CAN: ukjent id\r\n");
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
