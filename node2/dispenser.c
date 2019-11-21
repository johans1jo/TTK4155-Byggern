#include "dispenser.h"
#include "pwm.h"
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>

int state = 0;
int last_state = -1;
int operation = CLEAR_DISPENSER;

void dispenser_init() {
	// In CTC mode the counter is cleared to zero when the counter value (TCNTn) matches either the OCRnA (WGMn3:0 = 4)
	// Setter mode CTC (4)
	TCCR4B &= ~(1 << WGM43);
	TCCR4B |= (1 << WGM42);
	TCCR4A &= ~(1 << WGM41); // Be aware of A- and B-registers
	TCCR4A &= ~(0 << WGM40);

	// Normal port operation
	TCCR4A &= ~(1 << COM4B1);
	TCCR4A &= ~(1 << COM4B0);

	// Prescaler = 1024
	TCCR4B |= (1 << CS42);
	TCCR4B &= ~(1 << CS41);
	TCCR4B |= (1 << CS40);

	OCR4B = (F_CPU/1024)*1; //1 second
}

void dispenser_start_timer() {
	TIMSK4 |= (1 << OCIE4B);
}

void dispenser_stop_timer() {
	state = 0;
	TIMSK4 &= ~(1 << OCIE4B);

}

void dispenser_open() {
		pwm_dispenser_set_ms(0.9);
}

void dispenser_close() {
		pwm_dispenser_set_ms(2.1);
}

void dispenser_clear() {
	operation = CLEAR_DISPENSER;
	state = 0;
	dispenser_start_timer();

	/*
	dispenser_select_bottom();
	dispenser_close();
	_delay_ms(1000);
	dispenser_select_top();
	dispenser_open();
	_delay_ms(1000);*/
}

void dispenser_select_top() {
	PORTF &= ~(1 << PF0);
}

void dispenser_select_bottom() {
		PORTF |= (1 << PF0);
}

void dispenser_drop_ball() {
	operation = DROP_BALL;
	state = 0;
	dispenser_start_timer();
	/*
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
	_delay_ms(1000);*/
}

void dispenser_do() {
	if (last_state != state) {
		if (operation == CLEAR_DISPENSER) {
			printf("clear_disp\r\n");
			if (state == 1) {
				dispenser_select_bottom();
				dispenser_close();
			} else if (state == 2) {
				dispenser_select_top();
				dispenser_open();
				dispenser_stop_timer();
			}
		} else if (operation == DROP_BALL) {
			printf("drop_ball\r\n");
			if (state == 1) {
				dispenser_select_top();
				dispenser_close();
			} else if (state == 2) {
				dispenser_select_bottom();
				dispenser_open();
			} else if (state == 3) {
				dispenser_close();
			} else if (state == 4) {
				dispenser_select_top();
				dispenser_open();
				dispenser_stop_timer();
			}
		}
		last_state = state;
	}
}

ISR(TIMER4_COMPB_vect) {
	state++;
	TCNT4 = 0; // Reset counter
}
