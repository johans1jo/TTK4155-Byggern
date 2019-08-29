#include <avr/io.h>
#include "uart.h"

#define FOSC 4915200 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1 // 31


void main(void) {
  uart_init(MYUBRR);
  printf("Ting funker");
  /*

  // uart_transmit- og uart_receive-kallene under funker ikke
  // pga endrede funksjonsdeklarasjoner

  while (1) {
    if (uart_receive()) {
      unsigned char hei = uart_receive();
      uart_transmit ('o');
      uart_transmit ('k');
      uart_transmit (hei);
    }
  }*/
}
