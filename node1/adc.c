#include "adc.h"
#define F_CPU 4915200
#include <util/delay.h>

#define PCB 1

void adc_init() {
	MCUCR = (1 << SRE); // Enable XMEM
	SFIOR = (1 << XMM2); // Mask unused bits
}

int adc_read(int channel) {
	volatile char *adc = (char *) 0x1400;
	uint8_t command;
	if (PCB) {
		command = flip_bits(3 + channel); // Due to reverse wiring on the PBC
	} else {
		command = 3 + channel;
	}
	adc[0] = command;

	_delay_us(200);

	uint8_t value = adc[0];
	if (PCB) {
		value = flip_bits(value); // Due to reverse wiring on the PBC
	}

	return value;
}

uint8_t flip_bits(uint8_t value) {
	value = (value & 0xF0) >> 4 | (value & 0x0F) << 4;
	value = (value & 0xCC) >> 2 | (value & 0x33) << 2;
	value = (value & 0xAA) >> 1 | (value & 0x55) << 1;
	return value;
}
