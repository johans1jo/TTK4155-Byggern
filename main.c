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

	_delay_ms(10);

	mcp_write(MCP_CANCTRL, MODE_LOOPBACK);

	char mode = mcp_read(MCP_CANSTAT);
	while (!mode) {
		mode = mcp_read(MCP_CANSTAT);
	}

	printf("mode c: %c\r\n", mode);
	printf("mode x: %x\r\n", mode);

	menu_ptr menu = menu_init();
	menu_start(menu);

	return 0;
}
