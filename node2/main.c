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
#include "dispenser.h"

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
	dispenser_init();
	sei();
	printf("\r\nStart\r\n");

	while(1) {
		dispenser_do();
		int mode = mode_get();
		if (mode == MODE_IDLE) {
		} else if (mode == MODE_PLAY_GAME && !game_is_on()) {
			game_play();
		} else if (mode == MODE_STOP_GAME) {
			game_stop();
			mode_set(MODE_IDLE);
		}
	}

	printf("Quit\r\n");
	return 0;
}

// Tar imot CAN-melding
ISR(INT3_vect) {
	message_t receive = can_receive();
	printf("canid %d\r\n", receive.id);
	if (receive.id == MSG1_SET_MODE) {
		mode_set(receive.data[0]); // 0 = IDLE, 1 = GAME
	} else if (receive.id == MSG1_GAME_VALUES) {
		// Receive values from node1
		if (mode_get() == MODE_PLAY_GAME && game_is_initialized()) {
			game_update_from_node1(receive.data);
		}

	} else if (receive.id == MSG1_GAME_STOP) {
		// Quit game
		mode_set(MODE_STOP_GAME);

	} else if (receive.id == MSG1_DIFFICULTY) {
		// Set controller paramet
		game_set_difficulty(receive.data[0]);

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
