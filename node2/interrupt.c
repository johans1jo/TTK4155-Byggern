#include "interrupt.h"
#include <avr/io.h>
#include "mcp.h"
#include <avr/interrupt.h>
#include "MCP2515.h"

void interrupt_init() {
  EIMSK |= (1 << INT3);
  DDRB &= ~(1 << INT3);
  //EICRA bør settes til å svare på fallende kant
  EICRA |= (1 << ISC31);
  EICRA &= ~(1 << ISC30);

  sei();
}
