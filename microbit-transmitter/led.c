#include <stdint.h>
#include "gpio.h"

void ledgikt(int troll) {
	// Configure LED Matrix
	for(int i = 4; i <= 12; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTSET = (1 << i);
	}
	for(int i = 13; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	// Configure buttons
	//GPIO->PIN_CNF[17] = 0;
	//GPIO->PIN_CNF[26] = 0;

	//int sleep = 0;
	/*while(1) {
		if (!(GPIO->IN & (1 << 17))) {
			GPIO->OUTCLR = (1 << 4);
			GPIO->OUTSET = (1 << 13);
		}
		if (!(GPIO->IN & (1 << 26))) {
			GPIO->OUTSET = (1 << 4);
			GPIO->OUTCLR = (1 << 13);
		}

		sleep = 10000;
		while(--sleep);
	}*/

	if (troll == 1) {
		GPIO->OUTCLR = (1<<4);
		GPIO->OUTSET = (1<<13);
	} else {
		GPIO->OUTCLR = (1<<5);
		GPIO->OUTSET = (1<<14);
	}
}