#include "solenoid.h"
#include <avr/io.h>
#include <stdio.h>
#define F_CPU 16000000UL
#include <util/delay.h>

int solenoid_on = 0;

// Interruptdrevet solenoid!

void solenoid_init() {
  // Set ADC1 as input
  DDRF |= (1 << PF1);
	PORTF |= (1 << PF1); //high

	// Sett opp solenoid-timer-interrupt
}

void solenoid_set() {
	PORTF &= ~(1 << PF1); //low
	solenoid_on = 1;
}

void solenoid_clear() {
	PORTF |= (1 << PF1); //high
	solenoid_on = 0;
}

int solenoid_is_set() {
	return solenoid_on;
}

void solenoid_fire() {
	printf("solenoid_fire\r\n");
	if (!solenoid_is_set()) {
		solenoid_set();
		// Start timer for å stoppe solenoiden
		_delay_ms(100);
		solenoid_clear();
	}
}

/*
ISR {
	solenoid_clear();

	// Stopp clear-timer
}
*/
