#include "controller.h"
#include <stdio.h>
#include <avr/io.h>


int Kp = 3;
int Ki = 0;
int Tt = 20/1000;

unsigned long total_error = 0;

void controller_timer_init() {
	// In CTC mode the counter is cleared to zero when the counter value (TCNTn) matches either the OCRnA (WGMn3:0 = 4)
  // Setter mode CTC (4)
  TCCR3B &= ~(1 << WGM33);
	TCCR3B |= (1 << WGM32);
  TCCR3A &= ~(1 << WGM31); //obs
  TCCR3A &= ~(0 << WGM30);

  // Normal port operation
  TCCR3A &= ~(1 << COM3B1);
  TCCR3A &= ~(1 << COM3B0);

  // Prescaler = 1024
  TCCR3B |= (1 << CS32);
  TCCR3B &= ~(1 << CS31);
  TCCR3B |= (1 << CS30);

  //OCR3B sammenlignes kontinuerlig med counter (TCNT1)
	OCR3B = (F_CPU/1024)*0.02;
	printf("OCR3B: %x\r\n", OCR3B);

	// Enable timer 3 interrupt, compare match
	TIMSK3 |= (1 << OCIE3B); //(1 << TOIE3) overflow
}


int controller(int reference, int encoder_value) {
	int e = reference - encoder_value;
	total_error = total_error + e;
	unsigned int u = Kp*e + Tt*Ki*total_error;
	int k_ledd = Kp*e;
	int i_ledd = Tt*Ki*total_error;
	printf("total_error: %lu K-ledd: %d I-ledd: %d ", total_error, k_ledd, i_ledd);
	return u;
}
