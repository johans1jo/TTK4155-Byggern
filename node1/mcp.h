/**
 * @file
 * @brief Implements the necessary functions for the CAN driver
 */

/**
 * @brief Initializes the MCP2515 by calling spi_master_init() and mcp_reset().
 */
void mcp_init();

/**
 * @brief Reads a message.
 *
 * @return The message
 */
uint8_t mcp_read(uint8_t address);


void mcp_write(uint8_t address, uint8_t data);
void mcp_request_to_send(int buffer_number);
char mcp_read_status();
void mcp_bit_modify(uint8_t address, uint8_t mask, uint8_t data);
void mcp_reset();
void mcp_set_mode(uint8_t mode);
char mcp_get_mode();
