#include "game.h"
#include <avr/interrupt.h>
#include "motor.h"
#include "solenoid.h"
#include "servo.h"
#include "ir.h"
#include "encoder.h"

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
	game_on = 1;
	game_init();
	game_initialized = 1;
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
}

void game_update_from_node1(char* data) {
	int x = data[0];
	int y = data[1];
	int bj = data[2];
	int bl = data[3];
	int sl = data[4];
	int br = data[5];
	int sr = data[6];
}

int game_is_goal() {
	int ir = ir_get();
	if (ir < 300) {
		return 1;
	}
	return 0;
}

ISR(TIMER3_COMPB_vect) {
	if (game_initialized) {
		game_set_everything();
	}
	TCNT3 = 0; // Resetter telleren
}
