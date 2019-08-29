void uart_Init( unsigned int ubrr );

int uart_Transmit(char data, FILE * file);

int uart_Receive( FILE * file );


int transmit(char data, FILE *);
int receive(FILE *);
