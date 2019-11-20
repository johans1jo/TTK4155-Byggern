#include "led.h"
#include <avr/io.h>
#define F_CPU 4915200
#include <util/delay.h>

void led_init() {
	DDRE |= (1 << PORTE0); // Set led pin as output.
}

void led_set() {
	PORTE |= (1 << PORTE0); // Turn on led.
}

void led_clear() {
	PORTE &= ~(1 << PORTE0); // Turn off led.
}

void led_fire() {
	led_set();
	_delay_ms(1);
	led_clear();
}
