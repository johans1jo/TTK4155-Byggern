#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "adc.h"
#include <stdio.h>

void adc_init() {
  // Set ADC2 as input
  DDRF &= ~(1 << PF2);

  //AREF, Internal VREF turned off // Table 26-3
  //ADMUX &= ~(1 << REFS0);
  //ADMUX &= ~(1 << REFS1);

  //AVCC with external capacitor at AREF pin
  ADMUX |= (1 << REFS0);
  ADMUX &= ~(1 << REFS1);

  //Internal 1.1V Voltage Reference with external capacitor at AREF pin
  //ADMUX |= (1 << REFS0);
  //ADMUX |= (1 << REFS1);

  // single-ended ADC2 // Table 26-4
  ADMUX &= ~(1 << MUX0);
  ADMUX |= (1 << MUX1);
  ADMUX &= ~(1 << MUX2);
  ADMUX &= ~(1 << MUX3);
  ADMUX &= ~(1 << MUX4);
  ADCSRB &= ~(1 << MUX5);

  // Free running mode
  //ADMUX |= (1 << ADLAR);

  // ADC Enable
  //ADCSRA |= (1 << ADEN);
  ADCSRA |= (1 << ADEN)| (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2); //med prescaling
  //ADCSRA |= (1 << ADEN)|(1 << ADIE);

  // Start conversion --- will be cleared by hardware when the conversion is completed
  //ADCSRA |= (1 << ADSC);

}

char adc_read() {
  // single-ended ADC2 // Table 26-4
  //ADMUX |= (1 << MUX1);

  ADCSRA |= (1 << ADSC);
  //printf("ADMUX: %x\r\n", ADMUX);

	while(!(ADCSRA & (1<<ADIF))) {
  }
  int adc = ADCH*0b100000000 + ADCL;
  printf("ADC: %d\r\n", adc);
  return ADC;
}
