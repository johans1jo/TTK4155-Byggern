#include <avr/io.h>
#include <stdio.h>

void microbit_init(unsigned int ubrr);
void microbit_transmit(char data);
unsigned char microbit_receive();
