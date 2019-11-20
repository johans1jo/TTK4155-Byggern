#include "microbit.h"

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "adc.h"
#include <stdio.h>

#define SERVO_PIN PF3
#define SOLENOID_PIN PF4
#define SPEED_PIN PF5

void microbit_init() {
  // Set inputs
	DDRF &= ~(1 << SERVO_PIN);
	DDRF &= ~(1 << SOLENOID_PIN);
  DDRF &= ~(1 << SPEED_PIN);

  //AVCC with external capacitor at AREF pin
  ADMUX |= (1 << REFS0);
  ADMUX &= ~(1 << REFS1);

	/* from adc.c
  // single-ended ADC2 // Table 26-4
  ADMUX &= ~(1 << MUX0);
  ADMUX |= (1 << MUX1);
  ADMUX &= ~(1 << MUX2);
  ADMUX &= ~(1 << MUX3);
  ADMUX &= ~(1 << MUX4);
  ADCSRB &= ~(1 << MUX5);
	*/

  // ADC Enable
  ADCSRA |= (1 << ADEN)| (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2); // With prescaling
}

int microbit_read_servo_input() {
	ADMUX |= (0b11 << 2);
  ADCSRA |= (1 << ADSC);

	while(!(ADCSRA & (1<<ADIF))) {
  }
	int adcl = ADCL;
	int adch = ADCH;
	int adc = adch*0b100000000 + adcl;
  return adc;
}

int microbit_read_solenoid_input() {
	ADMUX |= (0b100 << 3);
  ADCSRA |= (1 << ADSC);

	while(!(ADCSRA & (1<<ADIF))) {
  }
	int adcl = ADCL;
	int adch = ADCH;
	int adc = adch*0b100000000 + adcl;
  return adc;
}

int microbit_read_speed_input() {
	ADMUX |= (0b101 << 3);
  ADCSRA |= (1 << ADSC);

	while(!(ADCSRA & (1<<ADIF))) {
  }
	int adcl = ADCL;
	int adch = ADCH;
	int adc = adch*0b100000000 + adcl;
  return adc;
}
