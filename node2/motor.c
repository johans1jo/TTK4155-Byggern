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

int Kp = 1;
int Ki = 0;
int Tt = 20/1000; // Change to float or double

void motor_init() {
	twi_init();

  DDRH |= (1 << DIR);
  //DDRH |= (1 << EN); // Enable
	motor_disable();

	motor_set_speed(0);
	motor_set_direction(RIGHT);
	motor_enable();
}

void motor_controller_init() {
	// In CTC mode the counter is cleared to zero when the counter value (TCNTn) matches either the OCRnA (WGMn3:0 = 4)
  // Setter mode CTC (4)
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

	OCR3B = (F_CPU/1024)*0.02;

	// Enable timer 3 interrupt, compare match
	TIMSK3 |= (1 << OCIE3B); //(1 << TOIE3) overflow
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

  // Adderss: 80
  // Command: 0
  unsigned char msg[] = {80, 0, speed};
  int msgSize = 3;
  twi_send(msg, msgSize); //TWI_Start_Transceiver_With_Data()
}

void motor_set_position(int reference) {
	reference = encoder_map(reference);
	unsigned int encoder_value = encoder_read();
	int e = reference - encoder_value;
	unsigned long total_error = 0;
	total_error = total_error + e; // Wrong
	unsigned int u = Kp*e + Tt*Ki*total_error;
	int k_ledd = Kp*e;
	int i_ledd = Tt*Ki*total_error;
	//printf("total_error: %lu K-ledd: %d I-ledd: %d ", total_error, k_ledd, i_ledd);
	int speed = abs(u)/40;
	if (e < 0) {
		motor_set_direction(RIGHT);
	} else {
		motor_set_direction(LEFT);
	}
	motor_set_speed(speed);
	//printf("Referanse: %d Encoder: %d Avvik: %d Padrag: %d Speed %d\r\n", reference, encoder_value, e, u, speed);
}

void motor_set_controller_parameters(int param_p, int param_i) {
	Kp = param_p;
	Ki = param_i;
}

int motor_get_controller_parameter_p() { return Kp; };
int motor_get_controller_parameter_i() { return Ki; };
