#include "motor.h"
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "twi.h"

#define SDA 20
#define SCL 21

#define DIR PH1
#define SEL PH3
#define EN PH4
#define OE PH5
#define RST PH6


void motor_init() {
  DDRH |= (1 << DIR);
  DDRH |= (1 << EN);
}

void motor_set_direction(direction_t dir) {
  if (dir == RIGHT) {
    PORTH &= ~(1 << DIR);
  } else {
    PORTH |= (1 << DIR);
  }

}

void motor_set_speed(int speedInt) {
  if (speedInt > 255) {
    speedInt = 255;
  } else if (speedInt < 0) {
    speedInt = 0;
  }
  char speed = speedInt;

  // Addresse: 80
  // Kommando: 0
  unsigned char msg[] = {80, 0, speed};
  int msgSize = 3;
  TWI_Start_Transceiver_With_Data(msg, msgSize); //twi_send()
}

void motor_enable() {
  PORTH |= (1 << EN);

}
void motor_disable() {
  PORTH &= ~(1 << EN);
}

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

  return msb*0b100000000 + lsb;
}

void encoder_reset() {
  PORTH &= ~(1 << RST);
  PORTH |= (1 << RST);
}
