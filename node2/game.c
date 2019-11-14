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

// Verdier fra multifunk
/*
int inputs = {
	0, //x	Joystick X
	0, //y	Joystick Y
	0, //bj	Button joystick
	0, //bl	Button left
	0, //br	Button right
	0, //sl	Slider left
	0  //sr	Slider right
}
*/

#define SCORE_TRESHOLD 200

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
	//printf("\r\n\r\n");
	game_on = 1;
	////printf("game_play 1\r\n");
	game_init();
	////printf("game_play 2\r\n");
	game_initialized = 1;
	//aktiver sett verdier-interrupt?
}

void game_stop() {
	game_on = 0;
	motor_disable();

	// Sender score til node1
	message_t score_msg = {
		200, //Score
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
		}
	} else if (ir > 300) {
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
	//printf("sl %d\r\n", sl);
	//printf("game_update_from_node1 x: %d y: %d bj: %d bl: %d br: %d sl: %d sr: %d\r\n", x, y, bj, bl, br, sl, sr);
}

/*
int game_is_goal() {
	int ir = ir_get();
	if (ir < 300) {
		return 1;
	}
	return 0;
}
*/

ISR(TIMER3_COMPB_vect) {
	////printf("TIMER3_COMPB_vect\r\n");
	////printf("init %d\r\n", game_initialized);
	if (game_initialized) {
		////printf("set things\r\n");
		game_set_everything();
	}
	TCNT3 = 0; // Resetter telleren
}
