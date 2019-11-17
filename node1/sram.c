#include "sram.h"

void sram_init() {
  MCUCR = (1 << SRE); //enable XMEM
  SFIOR = (1 << XMM2); //mask unused bits
}

void sram_write(uint16_t address, uint8_t data) {
  volatile char *ext_ram = (char *) 0x1800;
  ext_ram[address] = data;
}

uint8_t sram_read(uint16_t address) {
  volatile char *ext_ram = (char *) 0x1800;
  return ext_ram[address];
}
