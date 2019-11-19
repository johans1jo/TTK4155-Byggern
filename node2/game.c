#include "game.h"
#include <avr/interrupt.h>
#include "motor.h"
#include "solenoid.h"
#include "servo.h"
#include "ir.h"
#include "encoder.h"
#include <stdio.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "can.h"

#define SCORE_TRESHOLD 90

int x = 0;
int y = 0;
int bj = 0;
int bl = 0;
int br = 0;
int sl = 0;
int sr = 0;

int game_on = 0;
int game_initialized = 0;
int score = 0;
int scoring_now = 0;

void game_init() {
	motor_enable();
	encoder_calibrate();
	motor_controller_init();
	_delay_ms(100);
	motor_set_speed(0);
	motor_set_position(0);
	_delay_ms(1000);
}

void game_play() {
	game_on = 1;
	game_init();
	game_initialized = 1;
}

void game_stop() {
	game_on = 0;
	motor_disable();

	// Send score to node1
	message_t score_msg = {
		202,
		1,
		score
	};
	can_send(&score_msg);

	score = 0;
}

int game_is_on() {
	return game_on;
}

int game_is_initialized() {
	return game_initialized;
}

void game_set_everything() {
	// Motor
	int reference = -(sr - 127)*30;
	motor_set_position(reference);

	// Solenoid
	if (bl) {
		printf("bl %d\r\n", bl);
		solenoid_fire();
	}

	// Servo
	servo_set_from_joystick(y);

	// IR
	int ir = ir_read();
	if (!scoring_now) {
		int increase_score = (ir < SCORE_TRESHOLD);
		if (increase_score) {
			score++;
			scoring_now = 1;
			printf("score %d\r\n", score);

			// Send score message to node1
			message_t score_msg = {
				201,
				1,
				score
			};
			can_send(&score_msg);
			_delay_ms(100);
		}
	} else if (ir > SCORE_TRESHOLD) {
		scoring_now = 0;
	}
	//printf("game_set_everything x: %d y: %d bj: %d bl: %d br: %d sl: %d sr: %d\r\n", x, y, bj, bl, br, sl, sr);
}

void game_update_from_node1(char* data) {
	x = data[0];
	y = data[1];
	bj = data[2];
	bl = data[3];
	br = data[4];
	sl = data[5];
	sr = data[6];

	if (sl < 0) {
		sl = (255 + sl);
	}
	if (sr < 0) {
		sr = (255 + sr);
	}
	//printf("game_update_from_node1 x: %d y: %d bj: %d bl: %d br: %d sl: %d sr: %d\r\n", x, y, bj, bl, br, sl, sr);
}

ISR(TIMER3_COMPB_vect) {
	if (game_initialized) {
		game_set_everything();
	}
	TCNT3 = 0; // Reset counter
}
