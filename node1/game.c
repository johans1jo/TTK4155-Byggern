#include "game.h"
#include "can.h"
#include "mode.h"
#include "menu.h"
#define F_CPU 4915200
#include <util/delay.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>

int game_on = 0;

int game_is_on() {
	return game_on;
}

void game_init() {
	// In CTC mode the counter is cleared to zero when the counter value (TCNTn) matches either the OCRnA (WGMn3:0 = 4)
  // Setter mode CTC (4)
  TCCR3B &= ~(1 << WGM33);
	TCCR3B |= (1 << WGM32);
  TCCR3A &= ~(1 << WGM31); //obs
  TCCR3A &= ~(0 << WGM30);

  // Normal port operation
  TCCR3A &= ~(1 << COM3B1);
  TCCR3A &= ~(1 << COM3B0);

  // Prescaler = 1024
  TCCR3B |= (1 << CS32);
  TCCR3B &= ~(1 << CS31);
  TCCR3B |= (1 << CS30);

  //OCR3B sammenlignes kontinuerlig med counter (TCNT1)
	OCR3B = (F_CPU/1024)*0.1;
	//////printf("OCR3B: %x\r\n", OCR3B);

  // Normal port operation
  TCCR3A &= ~(1 << COM3B1);
  TCCR3A &= ~(1 << COM3B0);

	// Enable timer 3 interrupt, compare match
	//node1: TIMSK3 |= (1 << OCIE3B); //(1 << TOIE3) overflow
	//ETIMSK |= (1 << OCIE3B); //(1 << TOIE3) overflow
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

	printf("Sender CAN-mode-melding\r\n");

	message_t mode_msg = {
		100, //Mode-id
		1,
		GAME
	};
	can_send(&mode_msg);
	_delay_ms(100);

	// Setter igang timer-interrupt for å sende multifunkverdier
	game_timer_enable();
	game_on = 1;

	menu_ptr menu_in_game = menu_init(IN_GAME);
	menu_start(menu_in_game, CLEAR);

	// Her er vi stuck i while-løkka til in-game-menyen
}

void game_stop() {
	printf("Sender game-stop-melding\r\n");

	game_timer_disable();

	message_t stop_msg = {
		102, //Stop-id
		0,
	};
	can_send(&stop_msg);
	_delay_ms(100);

	game_on = 0;
}

void game_pause() {
	//pause?
}

void game_set_difficulty_hard() {
	game_set_controller_parameters(1,1);
}
void game_set_difficulty_medium() {
	game_set_controller_parameters(1,1);
}
void game_set_difficulty_easy() {
	game_set_controller_parameters(1,1);
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

ISR(TIMER3_COMPB_vect) {
	//printf("Sender multifunkverdier\r\n");
	can_send_everything();

	TCNT3 = 0; // Resetter telleren
}
