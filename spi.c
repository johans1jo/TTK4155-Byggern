#include "spi.h"
#include <avr/io.h>
#include "uart.h"
#include <avr/interrupt.h>
#include "MCP2515.h"

#define DDR_SPI DDRB
#define DD_SS PB4
#define DD_MOSI PB5
#define DD_MISO PB6
#define DD_SCK PB7

void spi_master_init() {
	printf("spcr1: %x\r\n", SPCR);
	/* Set MOSI and SCK - og SS - output, all others input */
	DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK)|(1<<DD_SS);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0)|(1<<SPIE);

	spi_set_ss();
	printf("spcr2: %x\r\n", SPCR);
}

void spi_slave_init() {
	/* Set MISO output, all others input */
	DDR_SPI = (1<<DD_MISO);
	/* Enable SPI */
	SPCR = (1<<SPE);
}

void spi_write(char cData) {
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF))) {
	}
}

char spi_read() {
	//SPDR = 0 ?
	/* Wait for reception complete */
	while(!(SPSR & (1<<SPIF))) {
	}
	/* Return data register */
	return SPDR;
}

void spi_set_ss() {
	PORTB = (1 << DD_SS);
}

void spi_clear_ss() {
	PORTB = (0 << DD_SS);
}
