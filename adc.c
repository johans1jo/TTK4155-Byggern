#include "adc.h"


void adc_init() {
  MCUCR = (1 << SRE); //enable XMEM
  SFIOR = (1 << XMM2); //mask unused bits

//	DDRE &= ~(1<<PINE0);
}

void adc_test() {

}
