#include <avr/io.h>
#include "uart.h"
#include <stdio.h>

//#define F_CPU 4915200
#define F_CPU 16000000UL
#include <util/delay.h>

#include <string.h>
#include "spi.h"
#include "MCP2515.h"
#include <avr/interrupt.h>
#include "MCP2515.h"
#include "mcp.h"
#include "can.h"
#include "pwm.h"
#include <time.h>
#include <stdlib.h>
#include "adc.h"
#include "score.h"
#include "twi.h"
#include "motor.h"

#define FOSC 16000000UL
#define BAUD 9600
//#define UBRR (FOSC/(16*BAUD))-1 //103. Riktig for U2Xn=0
#define UBRR 103

#define SDA 20
#define SCL 21

int main(void){
  uart_init(UBRR);
  adc_init();
  TWI_Master_Initialise();
  sei();

  //unsigned char address = 0b01010000;
  //unsigned char command = 0;
  //unsigned char data = 0b11111111;
  /*
  unsigned char msg[] = {80, 0, 200};
  int msgSize = 3;
  while (1) {
    TWI_Start_Transceiver_With_Data(msg, msgSize);
    _delay_ms(10);
  }*/

  encoder_init();
  while(1) {
    int hei = encoder_read();
    printf("encoder: %d", hei);
    _delay_ms(100);
  }

	return 0;
}

ISR(INT3_vect) {
  /*
	message_t receive = can_receive(); // Mottar melding
	if (receive.id == 10) { //x
		//x
		printf("x: %d\r\n", receive.data[0]);
    //servo_set_angle(receive.data[0]);
    servo_set_angle(receive.data[0]);
	} else if (receive.id == 11) { //y
		//y
		printf("y: %d\r\n\r\n", receive.data[0]);
	} else {
		if (receive.length > 8) {
			printf("Kaos. Meldingslengde: %d\r\n", receive.length);
		} else {
			printf("Heisann sveisann, vi har fått ei melding.\r\n");
			printf("Id: %d \r\n", receive.id);
			printf("Lengde: %d \r\n", receive.length);
			printf("Melding: %s \r\n\r\n", receive.data);
		}
	}
	// Resetter interrupt for motta-buffer0
	mcp_bit_modify(MCP_CANINTF, 0b1, 0);
  */
}

ISR(SPI_STC_vect) {
	//printf("\r\nSPI_STC_vect\r\n");
}

ISR(BADISR_vect) {
	printf("\r\nBADISR_vect\r\n");
}
