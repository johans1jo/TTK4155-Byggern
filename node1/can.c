#include <avr/io.h>
#include "can.h"
#include "mcp.h"
#include "MCP2515.h"
#include <stdio.h>
#include <avr/interrupt.h>
#include "adc.h"
#include "joystick.h"
#include "buttons.h"

void can_init() {
	mcp_init();
	mcp_set_mode(MODE_NORMAL);
	mcp_bit_modify(MCP_CANINTE, 0b11111111, 0b1); // Turn on receive0 interrupt. Turn off everything else.
}

void can_send(message_ptr message) {
	// Everything in here is about buffer 0

	// Id. TXBnSIDH og TXBnSIDL
	mcp_write(MCP_TXB0SIDH, message->id / 8); // 8 MSB bits in the ID
	mcp_write(MCP_TXB0SIDL, (message->id % 8) << 5); // 3 LSB bits in the ID

	// Length. TXBnDLC
	mcp_write(MCP_TXB0DLC, message->length);

	// Message. TXBnDm
	for (int i = 0; i < message->length; i++) {
		mcp_write(MCP_TXB0D0 + i, message->data[i]);
	}

	// Request to send
	mcp_request_to_send(0);
}

message_t can_receive() {
	// Everything in here is about buffer 0
	message_t message = {};

	// Id. RXBnSIDH og RXBnSIDL
	uint8_t id_low = mcp_read(MCP_RXB0SIDL)/0b100000;
	uint8_t id_high = mcp_read(MCP_RXB0SIDH);
	message.id = id_high * 0b1000 + id_low;

	// Length. RXBnDLC
	message.length = mcp_read(MCP_RXB0DLC);

	// Message. RXBnDM
	for (int i = 0; i < message.length; i++) {
		message.data[i] = mcp_read(MCP_RXB0D0 + i);
	}

	return message;
}

void can_send_everything() {
	int x = joy_read_x();
	int y = joy_read_y();
	int button_joystick = buttons_joystick();
	int button_left = buttons_left();
	int button_right = buttons_right();
	int slider_left = adc_read(SLIDER_LEFT);
	int slider_right = adc_read(SLIDER_RIGHT);
	//printf("x %d y %d bj %d bl %d br %d sl %d sr %d\r\n", x, y, button_joystick, button_left, button_right, slider_left, slider_right);

	message_t everything_msg = {
		101, //Multifunk-verdier-id
		7,
		x,
		y,
		button_joystick,
		button_left,
		button_right,
		slider_left,
		slider_right
	};
	can_send(&everything_msg);
}
