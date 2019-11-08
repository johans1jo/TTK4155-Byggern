#include "game.h"
#include <avr/interrupt.h>
#include "motor.h"
#include "solenoid.h"
#include "servo.h"
#include "ir.h"
#include "encoder.h"
#include <stdio.h>

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

void game_init() {
	encoder_calibrate();
}

void game_play() {
	cli();
	game_on = 1;
	printf("game_play 1\r\n");
	game_init();
	printf("game_play 2\r\n");
	game_initialized = 1;
	sei();
	//aktiver sett verdier-interrupt?
}

int game_is_on() {
	return game_on;
}

void game_set_everything() {
	// Motor
	int reference = sr*50;
	motor_set_position(reference);

	// Solenoid
	solenoid_fire();

	// Servo
	servo_set_from_joystick(y);

	printf("game_set_everything x: %d y: %d bj: %d bl: %d br: %d sl: %d sr: %d\r\n", x, y, bj, bl, br, sl, sr);
}

void game_update_from_node1(char* data) {
	x = data[0];
	y = data[1];
	bj = data[2];
	bl = data[3];
	br = data[4];
	sl = data[5];
	sr = data[6];

	printf("game_update_from_node1 x: %d y: %d bj: %d bl: %d br: %d sl: %d sr: %d\r\n", x, y, bj, bl, br, sl, sr);
}

int game_is_goal() {
	int ir = ir_get();
	if (ir < 300) {
		return 1;
	}
	return 0;
}

ISR(TIMER3_COMPB_vect) {
	printf("TIMER3_COMPB_vect\r\n");
	printf("init %d\r\n", game_initialized);
	if (game_initialized) {
		printf("set things\r\n");
		game_set_everything();
	}
	TCNT3 = 0; // Resetter telleren
}
