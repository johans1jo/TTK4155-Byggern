#include "buttons.h"
#include <avr/io.h>

void buttons_init() {
	DDRB &= ~(1 << JOYSTICK_BUTTON_PIN);
	DDRB &= ~(1 << LEFT_BUTTON_PIN);
	DDRB &= ~(1 << RIGHT_BUTTON_PIN);
}

int buttons_joystick() {
	return (PORTB & (1 << JOYSTICK_BUTTON_PIN));
}

int buttons_left() {
	return (PINB & (1 << LEFT_BUTTON_PIN));
	//return PINB1;
}

int buttons_right() {
	return (PORTB & (1 << RIGHT_BUTTON_PIN));
}
