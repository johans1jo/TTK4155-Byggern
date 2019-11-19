#include "led.h"
#include <avr/io.h>
#define F_CPU 4915200
#include <util/delay.h>

void led_init() {
	DDRE |= (1 << PORTE0);
}

void led_set() {
	PORTE |= (1 << PORTE0);
}

void led_clear() {
	PORTE &= ~(1 << PORTE0);
}

void led_fire() {
	led_set();
	_delay_ms(1);
	led_clear();
}
