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
#include "encoder.h"
#include "interrupt.h"
#include "controller.h"
#include "timer.h"

#define FOSC 16000000UL
#define BAUD 9600
//#define UBRR (FOSC/(16*BAUD))-1 //103. Riktig for U2Xn=0
#define UBRR 103

#define SDA 20
#define SCL 21

int main(void){
  uart_init(UBRR);
  adc_init();
  TWI_Master_Initialise(); //twi_init()
  pwm_init();
  motor_init();
  encoder_init();
  can_init(); // Denne initierer mcp, som initierer spi.
	timer_init();
  interrupt_init(); //inneholder litt CAN-interruptgreier

	printf("\r\n\r\nMainstart :)\r\n");

	_delay_ms(1000);
	motor_set_direction(RIGHT);
	motor_set_speed(0);
	motor_enable();
	encoder_reset();

	/*
	int reference = -2000;
  while(1) {
		unsigned int encoder = encoder_read(); //ok
		int e = reference - encoder; //ok
		int u = controller(reference, encoder);
		int speed = u/40;
		if (u < 0) {
			motor_set_direction(RIGHT);
			speed = -speed;
		} else {
			motor_set_direction(LEFT);
		}
		motor_set_speed(speed);
		printf("Referanse: %d Encoder: %d Avvik: %d Padrag: %d Speed %d\r\n", reference, encoder, e, u, speed);
		_delay_ms(20);
  }
	*/

	while(1) {
	}

	return 0;
}

ISR(INT3_vect) {
  //printf("hhheiiiii\r\n");

	message_t receive = can_receive(); // Mottar melding
	if (receive.id == 10) { //x
		//x
		printf("x: %d\r\n", receive.data[0]);
    //servo_set_angle(receive.data[0]);
    servo_set_angle(receive.data[0]);
	} else if (receive.id == 11) { //y
		//y
		printf("y: %d\r\n\r\n", receive.data[0]);
    if (receive.data[0] > 0) {
      //høyre
      //motor_set_direction(RIGHT);
      //motor_set_speed(receive.data[0]);
    } else {
      //venstre
      //motor_set_direction(LEFT);
      //motor_set_speed(receive.data[0]);
    }
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

}

ISR(SPI_STC_vect) {
	//printf("\r\nSPI_STC_vect\r\n");
}

ISR(BADISR_vect) {
	printf("\r\nBADISR_vect\r\n");
}

ISR(TIMER3_OVF_vect) {
	printf("\r\ntimer3-overflow\r\n");
}

ISR(TIMER3_COMPB_vect) {
	printf("timer3-compare\r\n");
	TCNT3 = 0;
}
