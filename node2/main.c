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
	printf("Start\r\n");

	while(1) {
		if (mode_get() == GAME && !game_is_on()) {
			printf("Game on:\r\n");
			game_play();
		}
	}

	return 0;
}

// Tar imot CAN-melding
// 100: modus
// 101: multifunk-data
// 102: stopp spill
ISR(INT3_vect) {
	message_t receive = can_receive();
	//printf("canid: %d\r\n", receive.id);
	//printf("candata: %s\r\n", receive.data);
	//game_update_from_node1(receive.data);
	if (receive.id == 100) {
		mode_set(receive.data[0]); // 0 = IDLE, 1 = GAME
/*
		//Responderer med modus:
		message_t mode_msg = {
			200,
			1,
			mode_get()
		};
		can_send(&mode_msg);
*/
	} else if (receive.id == 101) {
		// Receive values from node1
		if (mode_get() == GAME && game_is_initialized()) {
			game_update_from_node1(receive.data);
		}

	} else if (receive.id == 102) {
		// Quit game
		game_stop();
		mode_set(IDLE);

	} else if (receive.id == 103) {
		// Set difficulty
		motor_set_controller_parameters(receive.data[0], receive.data[1]);

		// Respond with the new parameters
		message_t param_msg = {
			203,
			2,
			motor_get_controller_parameter_p(),
			motor_get_controller_parameter_i()
		};
		can_send(&param_msg);

	} else {
		printf("CAN!id %d\r\n", receive.id);
	}
	// Reset timer for receive0 buffer
	mcp_bit_modify(MCP_CANINTF, 0b1, 0);
}

ISR(SPI_STC_vect) {
}

ISR(BADISR_vect) {
	printf("\r\nbadisr\r\n");
}

ISR(TIMER3_OVF_vect) {
}
