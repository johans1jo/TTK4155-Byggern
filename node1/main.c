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
#include "highscore.h"
#include "interrupt.h"

#define FOSC 4915200// Clock Speed
#define BAUD 9600
#define UBRR FOSC/16/BAUD-1

int main(void){
	uart_init(UBRR);
	can_init(); // Denne initierer mcp, som initierer spi.
  adc_init();
  joy_calibrate();
	sram_init();
	oled_init();
	oled_clear();
	interrupt_init();
	draw_init();
	buttons_init();
	game_init();
	sei();

	DDRE |= (1 << PORTE0);
	PORTE |= (1 << PORTE0);

	menu_ptr menu_main = menu_init(MAIN);
	while(1) {
		printf("main while\r\n");
		menu_start(menu_main, CLEAR);
	}

	printf("farvel\r\n");

	return 0;
}

ISR(INT0_vect) {
	message_t receive = can_receive(); // Mottar melding
	if (receive.id == 200) {
		// Modus
		printf("modus %d\r\n", receive.data[0]);
	} else if (receive.id == 201) {
		// Tar imot score underveis i spillet når brukeren scorer
		game_show_score(receive.data[0]);
	} else if (receive.id == 202) {
		// Tar imot score
		printf("highscore can\r\n");
		highscore_save(receive.data[0], game_get_user());
	} else if (receive.id == 203) {
		// Parametre
		printf("param p %d i %d\r\n", receive.data[0], receive.data[1]);
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
