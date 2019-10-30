#include "motor.h"
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

#define SDA 20
#define SCL 21

#define DIR PH1
#define SEL PH3
#define EN PH4
#define OE PH5
#define RST PH6


void motor_init() {
  DDRH |= (1 << DIR); //DIR
  DDRH |= (1 << EN); //EN

  motor_enable();
}

void motor_set_direction(direction_t dir) {
  if (dir == RIGHT) {
    PORTH &= ~(1 << DIR);
  } else {
    PORTH |= (1 << DIR);
  }

}
void motor_enable() {
  PORTH |= (1 << EN);

}
void motor_disable() {
  PORTH &= ~(1 << EN);
}

void encoder_init() {
  //RST lav // 0
  //RST høy PH6
  //OE lav PH5
  //SEL lav PH3
  //20 microsek
  //Les MSB
  //SEL høy
  //20 mikrosek
  //Les LSB
  DDRH |= (1 << SEL)|(1 << OE)|(1 << RST);
  PORTH &= ~(1 << RST);
  PORTH |= (1 << RST);
  PORTH &= ~(1 << OE);
}

int encoder_read() {
  PORTH &= ~(1 << SEL);
  _delay_us(20);
  //Les MSB A8-A15
  int msb = PORTC;
  PORTH |= (1<< SEL);
  _delay_us(20);
  int lsb = PORTC;

  return msb*0b100000000 + lsb;
}

void encoder_reset() {
  PORTH &= ~(1 << RST);
  PORTH |= (1 << RST);
}
