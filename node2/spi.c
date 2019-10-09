#include <avr/io.h>
#include "spi.h"
#include "uart.h"
#include <avr/interrupt.h>
#include "MCP2515.h"
#include <stdio.h>

#define DDR_SPI DDRB
#define DD_SS PB0
#define DD_MOSI PB2
#define DD_MISO PB3
#define DD_SCK PB1

void spi_master_init() {
	printf("spi_master_init\r\n");
	/* Set MOSI and SCK - og SS - output, all others input */
	DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK)|(1<<DD_SS);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0)|(1<<SPIE);

	spi_set_ss();
}

void spi_slave_init() {
	/* Set MISO output, all others input */
	DDR_SPI = (1<<DD_MISO);
	/* Enable SPI */
	SPCR = (1<<SPE);
}

void spi_write(char cData) {
	printf("spi_write: %x\r\n", cData);
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF))) {
		printf("w");
	}
	printf("spi_write :)");
}

uint8_t spi_read() {
	SPDR = 0xFF;
	/* Wait for reception complete */
	while(!(SPSR & (1<<SPIF))) {
		printf("r");
	}
	/* Return data register */
	return SPDR;
}

void spi_set_ss() {
	PORTB |= (1 << DD_SS);
}

void spi_clear_ss() {
	PORTB &= ~(1 << DD_SS);
}
