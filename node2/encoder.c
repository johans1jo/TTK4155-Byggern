#include "encoder.h"
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdio.h>

#define SDA 20
#define SCL 21

#define DIR PH1
#define SEL PH3
#define EN PH4
#define OE PH5
#define RST PH6

int encoder_init_value = 0;

void encoder_init() {
  DDRH |= (1 << SEL)|(1 << OE)|(1 << RST);
  DDRK = 0;

  PORTH &= ~(1 << RST);
  PORTH |= (1 << RST);
  PORTH |= (1 << OE);
}

int encoder_read() {
  PORTH &= ~(1 << OE);
  PORTH &= ~(1 << SEL);
  _delay_us(20);
  //Les MSB A8-A15
  int msb = PINK;
  PORTH |= (1<< SEL);
  _delay_us(20);
  int lsb = PINK;
  PORTH |= (1 << OE);

  return msb*0b100000000 + lsb - encoder_init_value;
}

void encoder_reset() {
  PORTH &= ~(1 << RST);
  PORTH |= (1 << RST);

	encoder_init_value = encoder_read();
	printf("Init: %d\r\n", encoder_init_value);
}
