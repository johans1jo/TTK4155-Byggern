#include "pwm.h"
#include <avr/io.h>
#include <stdio.h>

static unsigned int pwm_period = 0x9C40; //40.000

void pwm_init() {
  // Setter mode 14 aka 0b1110
  TCCR1B |= (1 << WGM13)|(1 << WGM12);
  TCCR1A |= (1 << WGM11);
  TCCR1A &= ~(0 << WGM10);

  // ICRn

  //COMnx = 0: no action on the OCnx Register is to be performed on the next compare match
  //If one or both of the COMnA1:0 bits are written to one, the OCnA output overrides the normal port functionality of the I/O pin it is connected to.
  //However, note that the Data Direction Register (DDR) bit corresponding to the OCnA, OCnB or OCnC pin must be set in order to enable the output driver
  /* The two Timer/Counter I/O locations (TCNTnH and TCNTnL, combined TCNTn) give direct access, both for read
     and for write operations, to the Timer/Counter unit 16-bit counter. To ensure that both the high and low bytes are
     read and written simultaneously when the CPU accesses these registers, the access is performed using an 8-bit
     temporary High Byte Register (TEMP)
  */

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

void pwm_set_ms(int ms) {
  if (ms < 0.9) {
    ms = 0.9;
  } else if (ms > 2.1) {
    ms = 2.1;
  }

  OCR1B = (pwm_period/0x14)*ms;
}
