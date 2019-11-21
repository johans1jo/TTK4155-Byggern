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
		MSG1_INPUT_SOURCE,
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

void game_set_on() {
	game_on = 1;
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
  //OCR3B is compared with counter (TCNT1) every clock cycle.
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
		MSG1_SET_MODE,
		1,
		MODE_PLAY_GAME
	};
	can_send(&mode_msg);

	// Wait for mode response from node2
}

void game_stop() {
	game_timer_disable();

	message_t stop_msg = {
		MSG1_GAME_STOP, //Stop-id
		0,
	};
	can_send(&stop_msg);

	game_on = 0;
}

void game_set_difficulty(int difficulty) {
	message_t difficulty_msg = {
		MSG1_DIFFICULTY,
		1,
		difficulty
	};
	can_send(&difficulty_msg);
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

		// Waiting for joystick to go back to initial position.
		while (joy_read_dir() != 0 || buttons_right()) {
			_delay_ms(10);
		};
		// Waiting for joystick to be pushed in some direction.
		while (joy_read_dir() == 0 && !buttons_right()) {
			_delay_ms(10);
		};

		if (buttons_right()) {
			if (keyboard_position > 26 && keyboard_position <= 30) {
				// Save
				mode_set(MODE_MAIN_MENU, 0);
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

void game_update_fails(int fails) {
	oled_goto_pos(7,0);
	char fails_str[2];
	sprintf(fails_str, "%d", fails);
	oled_print(fails_str);

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

void game_send_everything() {
	int x = joy_read_x();
	int y = joy_read_y();
	int button_joystick = buttons_joystick();
	int button_left = buttons_left();
	int button_right = buttons_right();
	int slider_left = adc_read(SLIDER_LEFT);
	int slider_right = adc_read(SLIDER_RIGHT);
	//printf("x %d y %d bj %d bl %d br %d sl %d sr %d\r\n", x, y, button_joystick, button_left, button_right, slider_left, slider_right);

	message_t everything_msg = {
		MSG1_GAME_VALUES,
		7,
		x,
		y,
		button_joystick,
		button_left,
		button_right,
		slider_left,
		slider_right
	};
	can_send(&everything_msg);
}

ISR(TIMER3_COMPB_vect) {
	game_send_everything();
	TCNT3 = 0; // Reset counter
}
