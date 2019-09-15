#include <stdlib.h>
#include <avr/io.h>
#include <stdio.h>

void sram_init();
void sram_test(void);

void sram_write(uint16_t address, uint8_t data);
uint8_t sram_read(uint16_t address) {
