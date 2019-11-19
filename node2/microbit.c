#include "microbit.h"

void microbit_init(unsigned int ubrr) {
	UBRR2H = 0;
	UBRR2L = 0;

	UCSR2C &= ~(1<<USBS2); // 2 stoppbit
	UCSR2C |= (3<<UCSZ20); // 8 bits per character

	UCSR2B = (1<<RXEN2)|(1<<TXEN2); // Enable receiver and transmitter

	UBRR2H = (ubrr >> 8); // 0
	UBRR2L = ubrr; // 103

	//fdevopen(uart_transmit, uart_receive); // fra uart.c
}


//int uart_transmit(char data, FILE * file) { // fra uart.c
//unsigned char?
void microbit_transmit(char data) {
	// Wait for empty transmit buffer
	while (! (UCSR2A & (1 << UDRE2)) );
	// Put data into buffer, sends the data
	UDR2 = data;
}

// int uart_receive(FILE * file){ // fra uart.c
unsigned char microbit_receive() {
	// Wait for data to be received
	while ( !(UCSR2A & (1 << RXC2)) );
	// Get and return received data from buffer
	return UDR2;
}
