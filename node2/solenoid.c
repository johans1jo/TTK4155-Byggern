#include "solenoid.h"
#include <avr/io.h>
#include <stdio.h>
#define F_CPU 16000000UL
#include <util/delay.h>

#define SOLENOID_PIN PF1

int solenoid_on = 0;

void solenoid_init() {
	DDRF |= (1 << SOLENOID_PIN); //output ADC1
	PORTF |= (1 << SOLENOID_PIN); //high

	// Solenoid timer interrupt init
}

void solenoid_set() {
	PORTF &= ~(1 << SOLENOID_PIN); //low
	solenoid_on = 1;
}

void solenoid_clear() {
	PORTF |= (1 << SOLENOID_PIN); //high
	solenoid_on = 0;
}

int solenoid_is_set() {
	return solenoid_on;
}

void solenoid_fire() {
	if (!solenoid_is_set()) {
		solenoid_set();

		// Turn on solenoid timer

		_delay_ms(100); // Remove
		solenoid_clear(); // Remove
	}
}

/*
ISR {
	solenoid_clear();

	// Turn off solenoid timer
}
*/
