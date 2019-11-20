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
#include "led.h"
#include "microbit.h"

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
	led_init();
	sei();
	printf("\r\nStart\r\n");

	while(1) {
		if (mode_get() == MODE_PLAY_GAME && !game_is_on()) {
			printf("Game on:\r\n");
			game_play();
		}
	}

	printf("Quit\r\n");
	return 0;
}

// Tar imot CAN-melding
ISR(INT3_vect) {
	message_t receive = can_receive();
	if (receive.id == MSG1_SET_MODE) {
		mode_set(receive.data[0]); // 0 = IDLE, 1 = GAME
		/*
		//Responderer med modus:
		message_t mode_msg = {
			MSG2_MODE_RESPONSE,
			1,
			mode_get()
		};
		can_send(&mode_msg);
		*/
	} else if (receive.id == MSG1_GAME_VALUES) {
		// Receive values from node1
		if (mode_get() == MODE_PLAY_GAME && game_is_initialized()) {
			game_update_from_node1(receive.data);
		}

	} else if (receive.id == MSG1_GAME_STOP) {
		// Quit game
		game_stop();
		mode_set(MODE_IDLE);

	} else if (receive.id == MSG1_CONTROLLER_PARAMETERS) {
		// Set difficulty
		motor_set_controller_parameters(receive.data[0], receive.data[1]);

	} else if (receive.id == MSG1_INPUT_SOURCE) {
		game_set_input_source(receive.data[0]);
	} else {
		printf("CAN!id %d\r\n", receive.id);
	}
	// Reset interrupt for receive0 buffer
	mcp_bit_modify(MCP_CANINTF, 0b1, 0);
}

ISR(SPI_STC_vect) {
}

ISR(BADISR_vect) {
	printf("\r\nbadisr\r\n");
}
