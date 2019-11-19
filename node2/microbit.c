#include "microbit.h"

void microbit_init(unsigned int ubrr) {
	UBRR0H = 0;
	UBRR0L = 0;

	UCSR0C = (1<<USBS0); // 2 stoppbit
	UCSR0C = (3<<UCSZ00); // 8 bits per character

	UCSR0B = (1<<RXEN0)|(1<<TXEN0); // Enable receiver and transmitter

	UBRR0H = (ubrr >> 8); // 0
	UBRR0L = ubrr; // 103

	//fdevopen(uart_transmit, uart_receive); // fra uart.c
}


//int uart_transmit(char data, FILE * file) { // fra uart.c
//unsigned char?
void microbit_transmit(char data) {
	// Wait for empty transmit buffer
	while (! (UCSR0A & (1 << UDRE0)) );
	// Put data into buffer, sends the data
	UDR0 = data;
}

// int uart_receive(FILE * file){ // fra uart.c
unsigned char microbit_receive() {
	// Wait for data to be received
	while ( !(UCSR0A & (1 << RXC0)) );
	// Get and return received data from buffer
	return UDR0;
}
