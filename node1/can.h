/**
 * @file
 * @brief A driver for the CAN which implements communication between nodes over CAN.
 */

 #include <avr/io.h>

/**
 * @struct A struct with the id, length of the data, and the data of the message.
 */
typedef struct Message {
	unsigned int id; /**< The id of the message */
	uint8_t length;  /**< The length of the data bytes of the message */
	char data[8];    /**< The data of the message */
} message_t, *message_ptr;

/**
 * @brief Initializes the CAN by calling the function mcp_init
 */
void can_init();

/**
 * @brief Sends a message to the nodes over CAN. Sets the 11-bit message-id by setting the 8 higher bits in the TXB0SIDH register
 * and the 3 lower bits in the TXB0SIDL register of the MCP2515, sets the number of data bytes to be transmitted in the
 * TXB0DLC register, and writes data bytes to the TXBnDm register(s).

 * @param[in] message Takes a pointer to the Message-struct we would like to send.
 */
void can_send(message_ptr message);


/**
 * @brief Reads a message sent over CAN. Assembles the id of the received message by reading the 8 higher bits in the RXB0SIDL register
 * and the 3 lower bits in the RXB0SIDH register, reads the number of data bytes transmitted by reading the RXB0DLC register, and reads the data bytes
 * from the RXBnDm register(s).

 * @return The data byte(s) of the received message from the RXBnDm register(s).
 */
message_t can_receive();

/**
 * @brief Bare tull!
 */
void can_interrupt();
void can_send_everything();
