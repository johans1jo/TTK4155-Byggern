#include "pwm.h"
#include <avr/io.h>
#include <stdio.h>

static unsigned int pwm_period = 0x9C40; //40.000

void pwm_init() {
	// Shooting servo JP12 (JP6-p7)
	// Setter mode 15 aka 0b1111
	TCCR1B |= (1 << WGM13)|(1 << WGM12);
	TCCR1A |= (1 << WGM11);
	TCCR1A &= ~(1 << WGM10);

	// Set at BOTTOM, clear at compare match
	TCCR1A |= (1 << COM1B1);
	TCCR1A &= ~(1 << COM1B0);

	// Prescaler = 8
	TCCR1B &= ~(1 << CS12);
	TCCR1B |= (1 << CS11);
	TCCR1B &= ~(1 << CS10);

	ICR1 = pwm_period; //40.000

	pwm_shoot_set_ms(1); // Change

	// Set OC1A as output
	DDRB |= (1 << PB6);



	// Dispenser servo 1-2 JP11 (JP6-p6)
	// Disp1 - OC1A - PB5
	//TCCR1B |= (1 << WGM13)|(1 << WGM12);
	//TCCR1A |= (1 << WGM11);
	//TCCR1A &= ~(0 << WGM10);

	// Set at BOTTOM, clear at compare match
	TCCR1A |= (1 << COM1A1);
	TCCR1A &= ~(1 << COM1A0);

	// Prescaler = 8
	//TCCR1B &= ~(1 << CS12);
	//TCCR1B |= (1 << CS11);
	//TCCR1B &= ~(1 << CS10);

	//ICR1 = pwm_period; //40.000

	pwm_dispenser_set_ms(1); // Change

	// Set OC1A as output
	DDRB |= (1 << PB5);



	// Servo switch pin
	DDRF |= (1 << PF0);
}

void pwm_shoot_set_ms(double ms) {
  if (ms < 0.9) { // 0.9
    ms = 0.9;
  } else if (ms > 2.1) { // 2.1
    ms = 2.1;
  }

  OCR1B = (pwm_period/0x14)*ms;
}


void pwm_dispenser_set_ms(double ms) {
  if (ms < 0.9) { // 0.9
    ms = 0.9;
  } else if (ms > 2.1) { // 2.1
    ms = 2.1;
  }

  OCR1A = (pwm_period/0x14)*ms;
}
