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

int initial_value = 0;
int max_left = 0;
int max_right = 0;

void encoder_init() {
	DDRH |= (1 << SEL)|(1 << OE)|(1 << RST);
	DDRK = 0;

	PORTH &= ~(1 << RST);
	PORTH |= (1 << RST);
	PORTH |= (1 << OE);

	encoder_reset();
}

void encoder_reset() {
	PORTH &= ~(1 << RST);
	PORTH |= (1 << RST);
}

void encoder_calibrate() {
	int enc = encoder_read();
	motor_set_speed(100);
	motor_set_direction(LEFT);
	_delay_ms(1000);
	while (abs(enc - encoder_read()) > 100) {
		enc = encoder_read();
		_delay_ms(1000);
	}
	max_left = enc;
	motor_set_direction(RIGHT);
	_delay_ms(1000);
	while (abs(enc - encoder_read()) > 100) {
		enc = encoder_read();
		_delay_ms(100);
	}
	max_right = enc;
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

	return msb*0b100000000 + lsb - initial_value;
}

int encoder_map(int reference) {
	int diff = max_left - max_right;
	int middle = max_right + diff/2;
	int mapped = middle + reference;
	return mapped;
}
