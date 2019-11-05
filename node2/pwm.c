#include "pwm.h"
#include <avr/io.h>
#include <stdio.h>

static unsigned int pwm_period = 0x9C40; //40.000

void pwm_init() {
  // Setter mode 14 aka 0b1110
  TCCR1B |= (1 << WGM13)|(1 << WGM12);
  TCCR1A |= (1 << WGM11);
  TCCR1A &= ~(0 << WGM10);

  // Set at BOTTOM, clear at compare match
  TCCR1A |= (1 << COM1B1);
  TCCR1A &= ~(1 << COM1B0);

  // Prescaler = 8
  TCCR1B &= ~(1 << CS12);
  TCCR1B |= (1 << CS11);
  TCCR1B &= ~(1 << CS10);

  // Counter økes helt til den treffer ICR1 ?
  ICR1 = pwm_period; //40.000

  //OCR1A sammenlignes kontinuerlig med counter (TCNT1)
  pwm_set_ms(1);

  // Setter OC1A som output
  DDRB |= (1 << PB6);

}

void pwm_set_ms(double ms) {
  if (ms < 0.9) { // 0.9
    ms = 0.9;
  } else if (ms > 2.4) { // 2.1
    ms = 2.4;
  }

  OCR1B = (pwm_period/0x14)*ms;
}

void servo_set_angle(double angle) {
  angle = (angle + 30) * 1.8;
  double ms = 1.5 + (0.5 / 90.0) * angle;
  pwm_set_ms(ms);
}

int joy_to_deg(int pos) {
  return pos * 90 / 100;
}