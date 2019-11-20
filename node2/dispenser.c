#include "pwm.h"
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>

void dispenser_open() {
		pwm_dispenser_set_ms(0.9);
}

void dispenser_close() {
		pwm_dispenser_set_ms(2.1);
}

void dispenser_init() {
	dispenser_select_bottom();
	dispenser_close();
	_delay_ms(1000);
	dispenser_select_top();
	dispenser_open();
	_delay_ms(1000);
}

void dispenser_select_top() {
	PORTF &= ~(1 << PF0);
}

void dispenser_select_bottom() {
		PORTF |= (1 << PF0);
}

void dispenser_drop_ball() {
	dispenser_select_top();
	dispenser_close();
	_delay_ms(1000);
	dispenser_select_bottom();
	dispenser_open();
	_delay_ms(1000);
	dispenser_close();
	_delay_ms(1000);
	dispenser_select_top();
	dispenser_open();
	_delay_ms(1000);
	/*
	dispenser_open();
	_delay_ms(1000);
	dispenser_close();
	_delay_ms(1000);
	PINF |= (1 << PF0);
	PINF &= ~(1 << PF0);
	_delay_ms(100);

	dispenser_open();
	_delay_ms(1000);
	dispenser_close();
	_delay_ms(1000);
	PINF |= (1 << PF0);
	PINF &= ~(1 << PF0);
	*/

}
