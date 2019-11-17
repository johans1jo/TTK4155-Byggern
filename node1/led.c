#include "led.h"
#include <avr/io.h>

void led_init() {
	DDRE |= (1 << PORTE0); // Set led pin as output.
}

void led_set() {
	PORTE |= (1 << PORTE0); // Turn on led.
}

void led_clear() {
	PORTE &= ~(1 << PORTE0); // Turn off led.
}
