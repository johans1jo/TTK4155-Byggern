#include "motor.h"
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "twi.h"
#include <stdio.h>
#include "encoder.h"
#include <stdlib.h>

#define SDA 20
#define SCL 21

#define DIR PH1
#define SEL PH3
#define EN PH4
#define OE PH5
#define RST PH6

int Kp = 1; // Controller parameters in use at the moment
int Ki = 1; // ...
int Kp_user = 1; // User defined controller parameters
int Ki_user = 1; // ...
int Kp_init = 1; // Initial parameters. Used in encoder_calibrate()
int Ki_init = 1; // ...

void motor_init() {
	twi_init();

  DDRH |= (1 << DIR);
  //DDRH |= (1 << EN); // Enable
	motor_disable();

	motor_set_speed(0);
	motor_set_direction(RIGHT);
	motor_enable();
}

void motor_enable() {
  PORTH |= (1 << EN);
}

void motor_disable() {
  PORTH &= ~(1 << EN);
}

void motor_set_direction(direction_t dir) {
  if (dir == RIGHT) {
    PORTH &= ~(1 << DIR);
  } else {
    PORTH |= (1 << DIR);
  }
}

void motor_set_speed(int speedInt) {
  if (speedInt > 255) {
    speedInt = 255;
  } else if (speedInt < 0) {
    speedInt = 0;
  }
  char speed = speedInt;

  // Address: 80
  // Command: 0
  unsigned char msg[] = {80, 0, speed};
  int msgSize = 3;
  twi_send(msg, msgSize);
}

void motor_set_position(int reference) {
	reference = encoder_map(reference);
	unsigned int encoder_value = encoder_read();
	int e = reference - encoder_value;
	unsigned int u = Kp*e;
	int speed = abs(u)/40;
	if (e < 0) {
		motor_set_direction(RIGHT);
	} else {
		motor_set_direction(LEFT);
	}
	motor_set_speed(speed);
}

void motor_set_controller_parameters(int param_p, int param_i) {
	Kp_user = param_p;
	Kp = param_p;
	Ki_user = param_i;
	Ki = param_i;
}

int motor_get_controller_parameter_p() { return Kp; };

int motor_get_controller_parameter_i() { return Ki; };

void motor_clear_controller_parameters() {
	Kp = Kp_init;
	Ki = Ki_init;
}

void motor_set_user_defined_controller_parameters() {
	Kp = Kp_user;
	Ki = Ki_user;
}
