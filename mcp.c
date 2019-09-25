#include <avr/io.h>
#include "mcp.h"
#include "spi.h"
#include "MCP2515.h"

void mcp_init() {
	mcp_reset();
}

char mcp_read(uint8_t address) {
	spi_clear_ss();
	spi_write(MCP_READ);
	spi_write(address);
	char data = spi_read();
	spi_set_ss();

	return data;
}

void mcp_write(uint8_t address, uint8_t data) {
	spi_clear_ss();
	spi_write(MCP_WRITE);
	spi_write(address);
	spi_write(data);
	spi_set_ss();
}

void mcp_request_to_send(int buffer_number) {
	spi_clear_ss();
	buffer_number = buffer_number % 3; // Mapper buffernummer til 0, 1, 2
	char data = MCP_RTS_TX0;
	if (buffer_number == 0) {
		data = MCP_RTS_TX0;
	} else if (buffer_number == 1) {
		data = MCP_RTS_TX1;
	} else if (buffer_number == 2) {
		data = MCP_RTS_TX2;
	}
	spi_write(data);
	spi_set_ss();
}

char mcp_read_status() {
	spi_clear_ss();
	spi_write(MCP_READ_STATUS);
	char data = spi_read();
	spi_set_ss();

	return data;
}

void mcp_bit_modify(uint8_t address, uint8_t mask, uint8_t data) {
	spi_clear_ss();
	spi_write(MCP_BITMOD);
	spi_write(address);
	spi_write(mask);
	spi_write(data);
	spi_set_ss();
}

void mcp_reset() {
	spi_set_ss();
	spi_write(MCP_RESET);
	spi_clear_ss();
}

void mcp_set_mode(uint8_t mode) {
	spi_clear_ss();
	mcp_bit_modify(MCP_CANCTRL, 0b11100000, mode); // Eller bare skrive rett til adressen?
	spi_set_ss();
}

char mcp_get_mode() {
	char data = mcp_read(MCP_CANSTAT); // Ikke spi_read()

	return data;
}
