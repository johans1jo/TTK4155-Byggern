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
 * @return The message.
 */
uint8_t mcp_read(uint8_t address);

/**
 * @brief Writes a message with an address and data.
 *
 * @param The address.
 *
 * @param The data.
 */
void mcp_write(uint8_t address, uint8_t data);

/**
 * @brief Requests to send to buffer number 0, 1 or 2.
 *
 * @param The buffer number.
 */
void mcp_request_to_send(int buffer_number);

/**
 * @brief Reads the status.
 *
 * @return The status.
 */
char mcp_read_status();

/**
 * @brief Bit modifies the data at the given address.
 *
 * @param The address.
 *
 * @param The bits to be masked.
 *
 * @param The data.
 */
void mcp_bit_modify(uint8_t address, uint8_t mask, uint8_t data);

/**
 * @brief Resets the mcp.
 */
void mcp_reset();

/**
 * @brief Sets the mode by writing to the CANCTRL register.
 */
void mcp_set_mode(uint8_t mode);
char mcp_get_mode();
