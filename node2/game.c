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
#include "mode.h"
#include "dispenser.h"

#define FAIL_TRESHOLD 300

int x = 0;
int y = 0;
int bj = 0;
int bl = 0;
int br = 0;
int sl = 0;
int sr = 0;

int bl_previous = 0;

int game_on = 0;
int game_initialized = 0;
int fails = 0;
int failing_now = 0;
int input_source = JOYSTICKS;

int difficulty = EASY;

void game_init() {
	dispenser_init();
	motor_enable();
	motor_clear_controller_parameters();
	if (!game_is_initialized()) {
		encoder_calibrate();
	}
	motor_controller_init();
	_delay_ms(100);
	motor_set_position(0);
	_delay_ms(1000);
	motor_set_user_defined_controller_parameters();
}

void game_play() {
	game_on = 1;
	game_init();
	dispenser_drop_ball();

	//Responderer med modus:
	message_t mode_msg = {
		MSG2_MODE_RESPONSE,
		1,
		mode_get()
	};
	can_send(&mode_msg);

	game_initialized = 1;
}

void game_stop() {
	game_on = 0;
	motor_disable();

	message_t score_msg = {
		MSG2_SCORE_TOTAL,
		1,
		1 //score
	};
	can_send(&score_msg);

	fails = 0;
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
	if (bl && !bl_previous) {
		solenoid_fire();
	}
	bl_previous = bl;

	// Servo
	servo_set_from_joystick(y);

	// IR
	int ir = ir_read();
	if (!failing_now) {
		int increase_fails = (ir < FAIL_TRESHOLD);
		if (increase_fails) {
			fails++;
			failing_now = 1;

			message_t fail_msg = {
				MSG2_FAIL_INGAME,
				1,
				fails
			};
			can_send(&fail_msg);
			_delay_ms(100);
		}
	} else if (ir > FAIL_TRESHOLD) {
		failing_now = 0;
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

void game_set_input_source(int new_input_source) {
	input_source = new_input_source;
}

void game_set_difficulty(int new_difficulty) {
	difficulty = new_difficulty;
	printf("diff %d\r\n", difficulty);
	int Kp;
	int Ki;
	if (difficulty == EASY) {
		Kp = 1;
		Ki = 0;
	} else if (difficulty == MEDIUM) {
		Kp = 2;
		Ki = 3;
	} else if (difficulty == HARD) {
		Kp = 4;
		Ki = 5;
	}
	motor_set_controller_parameters(Kp, Ki);
}

ISR(TIMER3_COMPB_vect) {
	if (game_initialized) {
		game_set_everything();
	}
	TCNT3 = 0; // Reset counter
}
