typedef struct Message {
	uint8_t id;
	uint8_t length;
	unsigned char* data;
} message_t;

uint8_t can_id;
uint8_t length;
int can_i;
char * can_data;

void can_write(message_t message);
void can_read();
