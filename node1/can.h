#include <avr/io.h>

typedef struct Message {
	unsigned int id;
	uint8_t length;
	char data[8];
} message_t, *message_ptr;

void can_init();
void can_send(message_ptr message);
message_t can_receive();
void can_send_everything();
