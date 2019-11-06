/**
 *@file
 *@brief A driver for the CAN which implements communication between nodes over CAN
 */

typedef struct Message {
	unsigned int id;
	uint8_t length;
	char data[8];
} message_t, *message_ptr;

/**
 @brief Initializes the CAN by calling the function mcp_init

 
 */
void can_init();

/**
 @brief Sends a message to the nodes over CAN. Sets the message-id in the TXB0SIDH
 and TXB0SIDL registers of the MCP2515, sets the number of data bytes to be transmitted in the
 TXB0DLC register, and writes the registers beginning at TXB0D0.

 @param[in] message Takes a pointer to the Message-struct we would like to send
 */
void can_send(message_ptr message);
message_t can_receive();
void can_interrupt();
