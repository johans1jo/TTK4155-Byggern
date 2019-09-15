#include "adc.h"

#define F_CPU 4915200
#include <util/delay.h>

void adc_init() {
  MCUCR = (1 << SRE); //enable XMEM
  SFIOR = (1 << XMM2); //mask unused bits
}

int adc_read(int channel) {
  volatile char *adc = (char *) 0x1400;
  adc[0] = 3 + channel;

  //_delay_us(700);

  uint8_t value = adc[0];

  return value;
}
