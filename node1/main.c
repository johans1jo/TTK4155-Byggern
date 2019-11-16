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
#include "led.h"

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
	led_init();
	sei();
	led_set();

	menu_ptr menu_main = menu_init(MAIN);
	menu_ptr menu_in_game = menu_init(IN_GAME);
	menu_ptr menu_highscore = menu_init(HIGHSCORE);
	while(1) {
		printf("Main while\r\n");

		mode_t mode = mode_get();
		int parameter = mode_parameter_get();

		if (mode == MAIN_MENU) {
			printf("Mode: MAIN_MENU\r\n");

			menu_start(menu_main, CLEAR);

		} else if (mode == PLAY_GAME) {
			//printf("Mode: PLAY_GAME\r\n");

			if (parameter == 0) {
				game_play();
				//menu_ptr menu_in_game = menu_init(IN_GAME);
				menu_start(menu_in_game, CLEAR);

			} else if (parameter == 1) {
				game_stop();
				mode_set(MAIN_MENU, 0);

			} else if (parameter == 2) {
				game_pause();
			}

		} else if (mode == SHOW_HIGHSCORE) {
			//printf("Mode: SHOW_HIGHSCORE\r\n");

			highscore_show();
			menu_start(menu_highscore, DONT_CLEAR);

		} else if (mode == EDIT_USER) {
			//printf("Mode: EDIT_USER\r\n");

			game_edit_user(parameter);

		} else if (mode == CHOOSE_USER) {
			//printf("Mode: CHOOSE_USER\r\n");

			game_choose_user(parameter);

		} else if (mode == CHOOSE_DIFFICULTY) {
			//printf("Mode: CHOOSE_DIFFICULTY\r\n");

			game_set_difficulty(parameter);

		} else {
			//printf("Unknown mode\r\n");
			mode_set(MAIN_MENU, 0);
		}
	}

	//printf("Exit main\r\n");
	return 0;
}

ISR(INT0_vect) {
	printf("hei\r\n");
	message_t receive = can_receive(); // Mottar melding
	if (receive.id == 200) {
		// Modus
		//printf("modus %d\r\n", receive.data[0]);
	} else if (receive.id == 201) {
		// Tar imot score underveis i spillet når brukeren scorer
		printf("tar imot score :)\r\n");
		game_show_score(receive.data[0]);
	} else if (receive.id == 202) {
		// Tar imot score
		//printf("highscore can\r\n");
		highscore_save(receive.data[0], game_get_user());
	} else if (receive.id == 203) {
		// Parametre
		//printf("param p %d i %d\r\n", receive.data[0], receive.data[1]);
	} else {
		//printf("CAN: ukjent id\r\n");
	}
	// Resetter interrupt for motta-buffer0
	mcp_bit_modify(MCP_CANINTF, 0b1, 0);
}

ISR(SPI_STC_vect) {
	////printf("\r\nSPI_STC_vect\r\n");
}

ISR(BADISR_vect) {
	//printf("\r\nBADISR_vect\r\n");
}
