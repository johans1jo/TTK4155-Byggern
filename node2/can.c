#include <avr/io.h>
#include "can.h"
#include "mcp.h"
#include "MCP2515.h"
#include <stdio.h>
#include <avr/interrupt.h>

void can_init() {
	mcp_init();
  mcp_set_mode(MODE_NORMAL);

  // Interruptgreier
  mcp_bit_modify(MCP_CANINTE, 0b11111111, 0b1); // Skrur på receive0-interrupt. Skrur av alt annet.
  //mcp_bit_modify(MCP_CANINTE, 0b11111111, 0b11111111);
}

void can_send(message_ptr message) {
	cli();
	// Alt her foregår med buffer 0

	// Id. TXBnSIDH og TXBnSIDL
	mcp_write(MCP_TXB0SIDH, message->id / 8); // De åtte høyeste biteen i iden.
	mcp_write(MCP_TXB0SIDL, (message->id % 8) << 5); // De tre laveste bitene i iden. 2^3=8.

	// Lengde. TXBnDLC
	mcp_write(MCP_TXB0DLC, message->length);

	// Melding. TXBnDm
	for (int i = 0; i < message->length; i++) {
		mcp_write(MCP_TXB0D0 + i, message->data[i]);
	}

	// Request to send
	mcp_request_to_send(0);
	sei();
}

message_t can_receive() {
	// Alt her foregår med buffer 0
	message_t message = {};

	// Id. RXBnSIDH og RXBnSIDL
	//uint8_t id_low = (mcp_read(MCP_RXB0SIDL) & 0b11100000)/0b100000;
	//uint8_t id_high = mcp_read(MCP_RXB0SIDH);
	uint8_t id_low = mcp_read(MCP_RXB0SIDL)/0b100000;
	uint8_t id_high = mcp_read(MCP_RXB0SIDH);
	message.id = id_high * 0b1000 + id_low;

	// Lengde. RXBnDLC
	message.length = mcp_read(MCP_RXB0DLC);

	if (message.length <= 8) {
		// Melding. RXBnDM
		for (int i = 0; i < message.length; i++) {
			message.data[i] = mcp_read(MCP_RXB0D0 + i);
		}
	}

	return message;
}

void can_interrupt() {
	printf("2\r\n");
}
