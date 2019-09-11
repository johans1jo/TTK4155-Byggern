#include <avr/io.h>
#include "uart.h"
#include "sram.h"
#include "adc.h"

#define F_CPU 4915200
#include <util/delay.h>

#define FOSC 4915200 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1 // 31


void main(void) {
  uart_init(MYUBRR);
  adc_init();

  printf("start\n");

	volatile char *adc = (char *) 0x1400;

  while(1) {
    adc[0] = 0x04;

    _delay_us(700);

    uint8_t value = adc[0];

    printf("hei = %02X\n\n", value);
    _delay_ms(200);
  }
  printf("slutt");

}
