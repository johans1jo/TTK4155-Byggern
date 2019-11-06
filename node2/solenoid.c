#include "solenoid.h"
#include <avr/io.h>
#include <stdio.h>
#define F_CPU 16000000UL
#include <util/delay.h>

void solenoid_init() {
  // Set ADC1 as input
  DDRF |= (1 << PF1);
	PORTF |= (1 << PF1); //high
}

void solenoid_set() {
	PORTF &= ~(1 << PF1); //low
}

void solenoid_clear() {
	PORTF |= (1 << PF1); //high
}
