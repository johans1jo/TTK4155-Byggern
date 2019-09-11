#include <avr/io.h>
#define F_CPU 4915200
#include <util/delay.h>
#include "uart.h"
#include "sram.h"
#include "adc.h"


#define FOSC 4915200 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1 // 31


void main(void) {
  uart_init(MYUBRR);
  adc_init();

  while(1) {
    uint8_t value = adc_read(4);
    printf("hei = %02X\n\n", value);

    _delay_ms(200);
  }

}
