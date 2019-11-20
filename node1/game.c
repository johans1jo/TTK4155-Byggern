#include "game.h"
#include "can.h"
#include "mode.h"
#include "menu.h"
#define F_CPU 4915200
#include <util/delay.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "oled.h"
#include "string.h"
#include "draw.h"
#include "joystick.h"
#include <string.h>
#include "buttons.h"

int game_on = 0;
int user = 0;
int input_source = JOYSTICKS;

char users[5][20] = {
	"User 0",
	"User 1",
	"User 2",
	"User 3",
	"User 4"
};

void game_set_input_source(int new_input_source) {
	input_source = new_input_source;

	message_t input_msg = {
		104,
		1,
		new_input_source //1: joysticks, 2: microbit
	};
	can_send(&input_msg);
}

char * game_get_user_name(int user_id) {
	return users[user_id];
}

void game_set_user_name(int user_id, char * user_name) {
	strcpy(users[user_id], user_name);
}

int game_is_on() {
	return game_on;
}

void game_init() {
  // Set mode CTC (4)
  TCCR3B &= ~(1 << WGM33);
	TCCR3B |= (1 << WGM32);
  TCCR3A &= ~(1 << WGM31); // Be aware of A- and B-registers
  TCCR3A &= ~(0 << WGM30);
  // Normal port operation
  TCCR3A &= ~(1 << COM3B1);
  TCCR3A &= ~(1 << COM3B0);
  // Prescaler = 1024
  TCCR3B |= (1 << CS32);
  TCCR3B &= ~(1 << CS31);
  TCCR3B |= (1 << CS30);

	OCR3B = (F_CPU/1024)*0.1;
}

void game_timer_enable() {
	// Enable timer 3 interrupt, compare match
	ETIMSK |= (1 << OCIE3B);
}
void game_timer_disable() {
	// Disable timer 3 interrupt, compare match
	ETIMSK &= ~(1 << OCIE3B);
}

void game_play() {
	oled_clear();

	message_t mode_msg = {
		100, //Mode-id
		1,
		1 //game. fiks!
	};
	can_send(&mode_msg);
	_delay_ms(100);

	// Turn on timer interrupt for sending values to node2
	game_timer_enable();
	game_on = 1;
}

void game_stop() {
	game_timer_disable();

	message_t stop_msg = {
		102, //Stop-id
		0,
	};
	can_send(&stop_msg);

	game_on = 0;
}

void game_set_difficulty(int difficulty) {
	if (difficulty == 1) {
		game_set_controller_parameters(1,1); //Easy
	} else if (difficulty == 2) {
		game_set_controller_parameters(1,1); //Medium
	} else if (difficulty == 3) {
		game_set_controller_parameters(1,1); //Hard
	}
}

void game_set_controller_parameters(int param_p, int param_i) {
	message_t controller_msg = {
		103,
		2,
		param_p,
		param_i
	};
	can_send(&controller_msg);
}

void game_choose_user(int user_set) {
	user = user_set;
}
void game_edit_user(int user_edit) {
	oled_clear();
	draw_clear();
	char * user_name = game_get_user_name(user_edit);
	int user_name_length = strlen(user_name);
	int keyboard_position = 0;

	while(1) {
		draw_clear();
		draw_print(0, 0, user_name);
		draw_keyboard(keyboard_position);
		if (keyboard_position > 26 && keyboard_position <= 30) {
			draw_print(7, 0, "SAVE");
		} else {
			draw_print(7, 0, "Save");
		}
		if (keyboard_position > 30) {
			draw_print(7, 80, "ERASE");
		} else {
			draw_print(7, 80, "Erase");
		}

		draw_push();

		// Waiting for joystick to be placed in normal position
		while (joy_read_dir() != 0 || buttons_right()) {
			_delay_ms(10);
		};
		// Wait for joystick movement
		while (joy_read_dir() == 0 && !buttons_right()) {
			_delay_ms(10);
		};

		if (buttons_right()) {
			if (keyboard_position > 26 && keyboard_position <= 30) {
				// Save
				mode_set(MAIN_MENU, 0);
				return;

			} else if (keyboard_position > 30) {
				// Erase
				user_name[user_name_length - 1] = '\0';
				user_name_length--;
			} else {
				// New character in username
				char new_char;
				if (keyboard_position == 26) {
					new_char = ' ';
				} else {
					new_char = 'a' + keyboard_position;
				}
				user_name[user_name_length] = new_char;
				user_name_length++;
			}
		} else {
			// Update keyboard position
			int direction = joy_read_dir();
			if (direction == RIGHT) {
				if (keyboard_position > 26) {
					keyboard_position = 31;
				} else {
					keyboard_position++;
				}
			} else if (direction == LEFT) {
				if (keyboard_position > 26 && keyboard_position <= 30) {
					keyboard_position = 26;
				} else if (keyboard_position > 30) {
					keyboard_position = 27;
				} else {
					keyboard_position--;
				}
			} else if (direction == DOWN) {
				keyboard_position += 9;
			} else if (direction == UP) {
				keyboard_position -= 9;
			}

			if (keyboard_position < 0) {
				keyboard_position = 0;
			}
		}
	}
}

int game_get_user() {
	return user;
}

void game_update_score(int score) {
	oled_goto_pos(7,0);
	char score_str[2];
	sprintf(score_str, "%d", score);
	oled_print(score_str);

	/*
	// Fireworks :)
	draw_clear();
	for (int i = 0; i < 10; i++) {
		draw_fireworks(i);
		draw_push();
		_delay_ms(10);
	}
	*/
}

ISR(TIMER3_COMPB_vect) {
	can_send_everything();
	TCNT3 = 0; // Reset counter
}
