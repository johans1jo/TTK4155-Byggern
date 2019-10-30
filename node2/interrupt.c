#include "interrupt.h"
#include <avr/io.h>
#include "mcp.h"
#include <avr/interrupt.h>
#include "MCP2515.h"

void interrupt_init() {
  // Interruptgreier
  mcp_bit_modify(MCP_CANINTE, 0b11111111, 0b1); // Skrur på receive0-interrupt. Skrur av alt annet.
  //mcp_bit_modify(MCP_CANINTE, 0b11111111, 0b11111111); // Skrur på receive0-interrupt. Skrur av alt annet.

  EIMSK |= (1 << INT3);
  DDRB &= ~(1 << INT3);
  //EICRA bør settes til å svare på fallende kant
  EICRA |= (1 << ISC31);
  EICRA &= ~(1 << ISC30);

  sei();
}
