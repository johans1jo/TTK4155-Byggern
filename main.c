#include <avr/io.h>
#include "uart.h"
#include "sram.h"

#define F_CPU 4915200
#include <util/delay.h>

#define FOSC 4915200 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1 // 31


void main(void) {
  uart_init(MYUBRR);
  SRAM_init();
//  _delay_ms(3000);
  //SRAM_test();
  SRAM_test();
}
