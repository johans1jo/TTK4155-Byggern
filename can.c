#include <avr/io.h>
#include "can.h"
#include "mcp.h"
#include "MCP2515.h"
#include <stdio.h>
#include <avr/interrupt.h>


/*
uint8_t can_id = 0;
uint8_t can_length = 0;
int can_i = 0;
char * can_data = { 0 };
*/

/*
void can_write(message_t message) {
	mcp_write(MCP_TXB0SIDH, message.id);
	mcp_request_to_send(0);
	mcp_write(MCP_TXB0SIDH, message.length);
	mcp_request_to_send(0);
	for (int i = 0; i < message.length; i++) {
		mcp_write(MCP_TXB0SIDH,message.data[i]);
		mcp_request_to_send(0);
	}
}

void can_read() {
	if (!can_id) {
		can_id = mcp_read(MCP_RXB0SIDH);
		return;
	} else if (can_id == 1) {
		if (!can_length) {
			can_id = mcp_read(MCP_RXB0SIDH);
		} else {
			can_data[can_i] = mcp_read(MCP_RXB0SIDH);
		}
	}
}
*/
