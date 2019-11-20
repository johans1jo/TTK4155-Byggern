/**
 * @file
 * @brief A driver for the CAN.
 */

typedef struct Message {
	unsigned int id;
	uint8_t length;
	char data[8];
} message_t, *message_ptr;

/**
 * @brief Initializes the CAN.
 */
void can_init();

/**
 * @brief Sends a message to the nodes over CAN. Sets the 11-bit message-id by setting the 8 higher bits in the TXB0SIDH register
 * and the 3 lower bits in the TXB0SIDL register, sets the number of data bytes to be transmitted in the
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
