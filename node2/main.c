#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "uart.h"
#include "spi.h"
#include "MCP2515.h"
#include "mcp.h"
#include "can.h"
#include "pwm.h"
#include "adc.h"
#include "ir.h"
#include "twi.h"
#include "motor.h"
#include "encoder.h"
#include "solenoid.h"
#include "game.h"
#include "mode.h"

#define FOSC 16000000UL
#define BAUD 9600
//#define UBRR (FOSC/(16*BAUD))-1 //103. Riktig for U2Xn=0
#define UBRR 103

#define SDA 20
#define SCL 21

int main(void){
  uart_init(UBRR);
  adc_init();
  can_init();
  pwm_init();
  motor_init();
	encoder_init();
	solenoid_init();
	sei();
	printf("Node2 starter :)\r\n");

	while(1) {
		if (mode_get() == GAME && !game_is_on()) {
			////printf("Setter mode :)\r\n");
			printf("starter spillet\r\n");
			game_play();
		}
	}

	////printf("return 0:\r\n");
	return 0;
}

// Tar imot CAN-melding
// 100: modus
// 101: multifunk-data
// 102: stopp spill
ISR(INT3_vect) {
	message_t receive = can_receive();
	//game_update_from_node1(receive.data);
	if (receive.id == 100) {
		// Setter riktig modus
		mode_set(receive.data[0]); // 0 = IDLE, 1 = GAME
	} else if (receive.id == 101) {
		// Tar imot multifunk-verdier
		if (mode_get() == GAME && game_is_initialized()) {
			game_update_from_node1(receive.data);
		}
	} else if (receive.id == 102) {
		//Avslutter spillet
		game_stop();
		mode_set(IDLE);
	} else if (receive.id == 103) {
		// Sett vanskelighetsgrad
		motor_set_controller_parameters(receive.data[0], receive.data[1]);
	} else {
		printf("CAN: Ukjent id %d\r\n", receive.id);
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
	printf("\r\nTIMER3_OVF_vect\r\n");
}
