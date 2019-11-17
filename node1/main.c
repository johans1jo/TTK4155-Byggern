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

#define FOSC 4915200
#define BAUD 9600
#define UBRR FOSC/16/BAUD-1

int main(void){
	uart_init(UBRR);
	can_init();
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
	printf("Start\r\n");

	menu_ptr menu_main = menu_init(MAIN);
	menu_ptr menu_in_game = menu_init(IN_GAME);
	menu_ptr menu_highscore = menu_init(HIGHSCORE);
	while(1) {
		mode_t mode = mode_get();

		if (mode == MAIN_MENU) {
			menu_start(menu_main, CLEAR);

		} else if (mode == PLAY_GAME) {
			int parameter = mode_parameter_get();

			if (parameter == 0) {
				game_play();
				menu_start(menu_in_game, CLEAR);

			} else if (parameter == 1) {
				game_stop();
				mode_set(MAIN_MENU, 0);

			} else if (parameter == 2) {
				game_pause();
			}

		} else if (mode == SHOW_HIGHSCORE) {
			highscore_show();
			menu_start(menu_highscore, DONT_CLEAR);

		} else if (mode == EDIT_USER) {
			int user = mode_parameter_get();
			game_edit_user(user);
			game_choose_user(user);

		} else if (mode == CHOOSE_USER) {
			int user = mode_parameter_get();
			game_choose_user(user);
			mode_set(MAIN_MENU, 0);

		} else if (mode == CHOOSE_DIFFICULTY) {
			int difficulty = mode_parameter_get();
			game_set_difficulty(difficulty);

		} else {
			mode_set(MAIN_MENU, 0);
		}
	}
	return 0;
}

ISR(INT0_vect) {
	message_t receive = can_receive(); // Receive message.
	printf("CAN id: %d\r\n", receive.id);
	printf("CAN data: %s\r\n", receive.data);
	if (receive.id == 200) {
		// Mode
		//printf("modus %d\r\n", receive.data[0]);
	} else if (receive.id == 201) {
		// Receive score when user scores while playing.
		game_update_score(receive.data[0]);
	} else if (receive.id == 202) {
		// Receive score after ended game.
		//printf("highscore can\r\n");
		highscore_save(receive.data[0], game_get_user());
	} else if (receive.id == 203) {
		// Parametre =???????
		//printf("param p %d i %d\r\n", receive.data[0], receive.data[1]);
	} else {
		printf("CANid %d\r\n", receive.id);
	}
	// Reset interrupt for receive buffer 0.
	mcp_bit_modify(MCP_CANINTF, 0b1, 0);
}

ISR(SPI_STC_vect) {
}

ISR(BADISR_vect) {
	printf("badisr\r\n");
}
