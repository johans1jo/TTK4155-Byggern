#include "adc.h"

void adc_init() {
  MCUCR = (1 << SRE); //enable XMEM
  SFIOR = (1 << XMM2); //mask unused bits
}

uint8_t adc_read(int channel) {
  volatile char *adc = (char *) 0x1400;
  adc[0] = 3 + channel;

  //_delay_us(700);

  uint8_t value = adc[0];

  return value;
}

/*
int joy_read_x() {
  return adc_read(1);
}

int joy_read_y() {
  return adc_read(2);
}
*/
