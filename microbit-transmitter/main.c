#include "gpio.h"
//#include "led.c"
#include "twi.h"
#include "uart.h"
#include "utility.h"
#include <stdlib.h>
#include "ubit_led_matrix.h"

int main() {
	twi_init();	
	uart_init();
	ubit_led_matrix_init();

	uint8_t * data_buffer;
	data_buffer = (uint8_t*)malloc(8 * sizeof(uint8_t));



	ubit_led_matrix_light_only_at(0,1);

	twi_multi_read(0x1D, 0x0D, 1, data_buffer);
	//twi_multi_read(0x0D, 0x1D, 1, data_buffer);
	ubit_led_matrix_light_only_at(0,2);
	if (*data_buffer == 0x5A){
		ubit_led_matrix_light_only_at(1,1);
	} else {
		ubit_led_matrix_light_only_at(-1,-1);
	}

	//free(data_buffer);
	int sleep = 10000;

	while(--sleep);
	free(data_buffer);
		
	return 0;
}