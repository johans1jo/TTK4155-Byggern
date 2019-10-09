#include "uart.h"

void uart_init(unsigned int baud) {
	UBRR0H = 0;
	UBRR0L = 0;

	UCSR0C = (1<<USBS0); // 2 stoppbit
	UCSR0C = (3<<UCSZ00); // 8 bits per character

	UCSR0B = (1<<RXEN0)|(1<<TXEN0);

	UBRR0H = (baud >> 8); // 0
	UBRR0L = baud; // 103

	fdevopen(uart_transmit, uart_receive);
}

int uart_transmit(char data, FILE * file) {
    /* Wait for empty transmit buffer */
    while (! (UCSR0A & (1 << UDRE0)) );
    /* Put data into buffer, sends the data */
    UDR0 = data;
    return 0;
}

int uart_receive(FILE * file){
    /* Wait for data to be received */
    while ( !(UCSR0A & (1 << RXC0)) );
    /* Get and return received data from buffer */
    return UDR0;
}
