#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "adc.h"
#include <stdio.h>

void adc_init() {
	// Set ADC2 as input
	DDRF &= ~(1 << PF2);

	//AVCC with external capacitor at AREF pin
	ADMUX |= (1 << REFS0);
	ADMUX &= ~(1 << REFS1);

	// single-ended ADC2 // Table 26-4
	ADMUX &= ~(1 << MUX0);
	ADMUX |= (1 << MUX1);
	ADMUX &= ~(1 << MUX2);
	ADMUX &= ~(1 << MUX3);
	ADMUX &= ~(1 << MUX4);
	ADCSRB &= ~(1 << MUX5);

	// ADC Enable // These bits determine the division factor between the XTAL frequency and the input clock to the ADC.
	ADCSRA |= (1 << ADEN)| (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2); // With prescaling
}

int adc_read() {
	ADCSRA |= (1 << ADSC);

	while(!(ADCSRA & (1<<ADIF))) {
	}
	int adcl = ADCL;
	int adch = ADCH;
	int adc = adch*0b100000000 + adcl;
	return adc;
}
