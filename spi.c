#include "spi.h"
#include <avr/io.h>
#include "uart.h"
#include <avr/interrupt.h>

#define DDR_SPI DDRB
#define DD_SS PB4
#define DD_MOSI PB5
#define DD_MISO PB6
#define DD_SCK PB7

void spi_master_init(void) {
	/* Set MOSI and SCK output, all others input */
	DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK);
	/* Enable SPI, Master, set clock rate fck/16 */
	DDRB = (1 << PB4);
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0)|(1<<SPIE);
	//printf("\r\nMSTR etter master init: %d", SPCR & (1 << MSTR));

}

void spi_master_transmit(char cData) {
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF))) {
	}
}

void spi_slave_init(void) {
	/* Set MISO output, all others input */
	DDR_SPI = (1<<DD_MISO);
	/* Enable SPI */
	SPCR = (1<<SPE);
}

char spi_slave_receive(void) {
	/* Wait for reception complete */
	while(!(SPSR & (1<<SPIF))) {
	}
	/* Return data register */
	return SPDR;
}
