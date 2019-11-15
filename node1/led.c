#include "led.h"
#include <avr/io.h>

void led_init() {
	DDRE |= (1 << PORTE0);
}

void led_set() {
	PORTE |= (1 << PORTE0);
}

void led_clear() {
	PORTE &= ~(1 << PORTE0);
}
