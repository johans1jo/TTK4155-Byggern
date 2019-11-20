#include "solenoid.h"
#include <avr/io.h>
#include <stdio.h>
#define F_CPU 16000000UL
#include <util/delay.h>

#define SOLENOID_PIN PF1

int solenoid_on = 0;

// Interruptdrevet solenoid!

void solenoid_init() {
 DDRF |= (1 << SOLENOID_PIN); // Output ADC1
 PORTF |= (1 << SOLENOID_PIN); // High

 // Initialize solenoid timer interrupt
}

void solenoid_set() {
 PORTF &= ~(1 << SOLENOID_PIN); // Low
 solenoid_on = 1;
}

void solenoid_clear() {
 PORTF |= (1 << SOLENOID_PIN); // High
 solenoid_on = 0;
}

int solenoid_is_set() {
 return solenoid_on;
}

void solenoid_fire() {
	if (!solenoid_is_set()) {
		solenoid_set();
		// Start timer for clearing the solenoid, instead of the delay.
		_delay_ms(100); // Remove when interrupt is implemented
		solenoid_clear(); // Remove when interrupt is implemented
	}
}

/*
ISR {
	solenoid_clear();
	// Turn off the timer interrupt
}
*/
