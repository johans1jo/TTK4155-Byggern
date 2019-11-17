#include "twi.h"
#include "gpio.h"
#include "uart.h"

void twi_init(){
	GPIO->PIN_CNF[0]= (1<<10) | (1<<9) | (1<<3) | (1<<2);
	GPIO->PIN_CNF[30]= (1<<10) | (1<<9) | (1<<3) | (1<<2);

	TWI0->RXDREADY = 0;
	TWI0->TXDSENT = 0;//txdsent = 0;	
	TWI0->ERROR = 0;


	TWI0->PSELSCL = 0;
	TWI0->PSELSDA = 30;
	TWI0->FREQUENCY = 0x01980000;

	TWI0->ENABLE = 5;
}

void twi_multi_read(uint8_t slave_address, uint8_t start_register, int registers_to_read, uint8_t * data_buffer) {
	TWI0->ADDRESS = slave_address;
	TWI0->STARTTX = 1;
	TWI0->TXDSENT = 0;
	TWI0->TXD = start_register;
	uart_send('u');
	while (!TWI0->TXDSENT){
		uart_send('k');
	}
	
	//ledgikt(1);
	uart_send('i');
/*
	TWI0->STARTRX = 1;

	for (int i = 0; i < registers_to_read-1; i++) {
		data_buffer[i] = TWI0->RXD;
		while (!TWI0->RXDREADY) {}
		TWI0->RXDREADY = 0;
		TWI0->STARTRX = 1;
	}
	TWI0->STOP = 1;
	data_buffer[registers_to_read-1] = TWI0->RXD;
	*/
}


void twi_multi_write(uint8_t slave_address, uint8_t start_register, int registers_to_write, uint8_t* data_buffer) {}
