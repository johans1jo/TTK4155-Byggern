#include "encoder.h"
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdio.h>
#include "motor.h"
#include <stdlib.h>

#define SDA 20
#define SCL 21

#define DIR PH1
#define SEL PH3
#define EN PH4
#define OE PH5
#define RST PH6

int encoder_init_value = 0;
int encoder_max_left = 0;
int encoder_max_right = 0;

void encoder_init() {
  DDRH |= (1 << SEL)|(1 << OE)|(1 << RST);
  DDRK = 0;

  PORTH &= ~(1 << RST);
  PORTH |= (1 << RST);
  PORTH |= (1 << OE);
}

void encoder_calibrate() {
	motor_set_speed(100);
	motor_set_direction(LEFT);
	int enc = encoder_read();
	_delay_ms(1000);
	while (abs(enc - encoder_read()) > 100) {
		enc = encoder_read();
		_delay_ms(100);
	}
	encoder_max_left = enc;
	motor_set_speed(100);
	motor_set_direction(RIGHT);
	enc = encoder_read();
	_delay_ms(1000);
	while (abs(enc - encoder_read()) > 100) {
		enc = encoder_read();
		_delay_ms(100);
	}
	encoder_max_right = enc;

	int diff = abs(encoder_max_left - encoder_max_right);
	//blablabla
}

int encoder_read() {
  PORTH &= ~(1 << OE);
  PORTH &= ~(1 << SEL);
  _delay_us(20);
  //Les MSB A8-A15
  int msb = PINK;
  PORTH |= (1<< SEL);
  _delay_us(20);
  int lsb = PINK;
  PORTH |= (1 << OE);

  return msb*0b100000000 + lsb - encoder_init_value;
}

void encoder_reset() {
  PORTH &= ~(1 << RST);
  PORTH |= (1 << RST);

	encoder_init_value = encoder_read();
	printf("Init: %d\r\n", encoder_init_value);
}
