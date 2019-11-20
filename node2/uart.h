/**
 * @file
 * @brief A driver for the UART.
 */

#include <avr/io.h>
#include <stdio.h>

/**
 * @brief Initializes UART by setting baud rate, enabling receiver and transmitter,
 * and sets frame format to 8data and 2 stop bit.
 *
 * @param[in] The USART Baud Rate Register (UBRR).
 */
void uart_init(unsigned int ubrr);

/**
 * @brief Transmits data through UART by writing the data to the UDR0 buffer.
 *
 * @param[in] The data.
 * @param[in] A file-pointer to a file.
 */
int uart_transmit(char data, FILE * file);

/**
 * @brief Receives data through UART by reading the data in the UDR0 buffer.
 *
 * @param[in] A file-pointer to a file.
 */
int uart_receive(FILE * file);
