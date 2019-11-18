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

int game_on = 0;
int user = 0;

int game_is_on() {
	return game_on;
}

void game_init() {
  // Setter mode CTC (4)
  TCCR3B &= ~(1 << WGM33);
	TCCR3B |= (1 << WGM32);
  TCCR3A &= ~(1 << WGM31); //obs
  TCCR3A &= ~(1 << WGM30);
  // Normal port operation
  TCCR3A &= ~(1 << COM3B1);
  TCCR3A &= ~(1 << COM3B0);
  // Prescaler = 1024
  TCCR3B |= (1 << CS32);
  TCCR3B &= ~(1 << CS31);
  TCCR3B |= (1 << CS30);
  //OCR3B sammenlignes kontinuerlig med counter (TCNT1)
	OCR3B = (F_CPU/1024)*0.1;
}

void game_timer_enable() {
	// Enable timer 3 interrupt, compare match
	ETIMSK |= (1 << OCIE3B);
}
void game_timer_disable() {
	// Enable timer 3 interrupt, compare match
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

	// Setter igang timer-interrupt for å sende multifunkverdier
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

void game_pause() {
	//pause?
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
	// endre på user
}

int game_get_user() {
	return user;
}

void game_show_score(int score) {
	printf("mottar score\r\n");
	oled_goto_pos(10,10);
	char score_str[2];
	sprintf(score_str, "%d", score);
	oled_print(score_str);
}

ISR(TIMER3_COMPB_vect) {
	can_send_everything();
	TCNT3 = 0; // Resetter telleren
}
