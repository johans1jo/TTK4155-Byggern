#include <avr/io.h>
#include "uart.h"
#include "joystick.h"
#include <stdio.h>

#define F_CPU 4915200
#include <util/delay.h>

#include "oled.h"
#include <string.h>
#include "menu.h"
#include "spi.h"
#include "MCP2515.h"
#include <avr/interrupt.h>
#include "sram.h"
#include "draw.h"
#include "MCP2515.h"
#include "mcp.h"

#define FOSC 4915200// Clock Speed
#define BAUD 9600
#define UBRR FOSC/16/BAUD-1

int main(void){
	uart_init(UBRR);
	sram_init();
	adc_init();
	oled_init();
	oled_clear();
	draw_init();


	spi_master_init();
	mcp_init();

	mcp_set_mode(MODE_LOOPBACK);
	printf("mode: %x\r\n", mcp_read(MCP_CANSTAT));

	mcp_write(MCP_TXB0SIDH, 0xA7);
	mcp_request_to_send(0);
	uint8_t byte = mcp_read(MCP_RXB0SIDH);
	printf("mottar: %x\r\n", byte);

/*
	menu_ptr menu = menu_init();
	menu_start(menu);
*/
	return 0;
}
