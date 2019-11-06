#include "timer.h"
#include <avr/io.h>
#include <stdio.h>

//static unsigned int pwm_period = 0x9C40; //40.000

void timer_init() {
	// In CTC mode the counter is cleared to zero when the counter value (TCNTn) matches either the OCRnA (WGMn3:0 = 4)
  // Setter mode CTC (4)
  TCCR3B &= ~(1 << WGM33);
	TCCR3B |= (1 << WGM32);
  TCCR3A &= ~(1 << WGM31); //obs
  TCCR3A &= ~(0 << WGM30);

  // Normal port operation
  //TCCR3A &= ~(1 << COM3B1);
  //TCCR3A &= ~(1 << COM3B0);
  TCCR3A |= (1 << COM3B1);
  TCCR3A |= (1 << COM3B0);

  // Prescaler = 1024
  TCCR3B |= (1 << CS32);
  TCCR3B &= ~(1 << CS31);
  TCCR3B |= (1 << CS30);

  //OCR3B sammenlignes kontinuerlig med counter (TCNT1)
	OCR3B = (16000000UL/1024)*0.05;
	printf("OCR3B: %x\r\n", OCR3B);

	// Enable timer 3 interrupt, compare match
	TIMSK3 |= (1 << OCIE3B); //(1 << TOIE3) overflow
}

/*
void pwm_set_ms(double ms) {
  if (ms < 0.9) { // 0.9
    ms = 0.9;
  } else if (ms > 2.4) { // 2.1
    ms = 2.4;
  }

  OCR1B = (pwm_period/0x14)*ms;
}*/
