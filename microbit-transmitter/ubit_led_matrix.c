#include <stdint.h>
#include "ubit_led_matrix.h"
#include "gpio.h"

static void ubit_led_matrix_helper_disable_all_pins();
static void ubit_led_matrix_helper_translate_x_y_to_ground_supply(int * data);

void ubit_led_matrix_init(){
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}
}

void ubit_led_matrix_light_only_at(int x, int y){
	ubit_led_matrix_helper_disable_all_pins();

	int ground_supply[2] = {x, y};
	ubit_led_matrix_helper_translate_x_y_to_ground_supply(ground_supply);
	int ground_pin = ground_supply[0];
	int supply_pin = ground_supply[1];

	GPIO->OUTCLR = (1 << ground_pin);
	GPIO->OUTSET = (1 << supply_pin);
}

static void ubit_led_matrix_helper_disable_all_pins(){
	/*
	 * These magic numbers come from (1 << 13) | ... | (1 << 15)
	 * and (1 << 4) | ... | (1 << 12), respectively. They set the
	 * ground pins high, and the supply pins low.
	 */
	GPIO->OUTCLR = 57344;
	GPIO->OUTSET = 8176;
}

static void ubit_led_matrix_helper_translate_x_y_to_ground_supply(int * data){
	/*
	 * Expects the input to be an integer array of [x, y], will
	 * alter this array to contain [ground pin, supply pin].
	 */
	int x = data[0];
	int y = data[1];

	if(x > 2)
		x = 2;
	else if(x < -2)
		x = -2;
	if(y > 2)
		y = 2;
	else if(y < -2)
		y = -2;

	int ground;
	int supply;
	switch(y){
		case -2:
			switch(x){
				case -2:
					ground = 6;
					supply = 15;
					break;
				case -1:
					ground = 10;
					supply = 14;
					break;
				case 0:
					ground = 4;
					supply = 15;
					break;
				case 1:
					ground = 9;
					supply = 14;
					break;
				case 2:
					ground = 5;
					supply = 15;
					break;
			}
			break;
		case -1:
			switch(x){
				case -2:
					ground = 11;
					supply = 13;
					break;
				case -1:
					ground = 10;
					supply = 13;
					break;
				case 0:
					ground = 9;
					supply = 13;
					break;
				case 1:
					ground = 8;
					supply = 13;
					break;
				case 2:
					ground = 7;
					supply = 13;
					break;
			}
			break;
		case 0:
			switch(x){
				case -2:
					ground = 5;
					supply = 14;
					break;
				case -1:
					ground = 12;
					supply = 13;
					break;
				case 0:
					ground = 6;
					supply = 14;
					break;
				case 1:
					ground = 12;
					supply = 15;
					break;
				case 2:
					ground = 4;
					supply = 14;
					break;
			}
			break;
		case 1:
			switch(x){
				case -2:
					ground = 7;
					supply = 15;
					break;
				case -1:
					ground = 8;
					supply = 15;
					break;
				case 0:
					ground = 9;
					supply = 15;
					break;
				case 1:
					ground = 10;
					supply = 15;
					break;
				case 2:
					ground = 11;
					supply = 15;
					break;
			}
			break;
		case 2:
			switch(x){
				case -2:
					ground = 4;
					supply = 13;
					break;
				case -1:
					ground = 7;
					supply = 14;
					break;
				case 0:
					ground = 5;
					supply = 13;
					break;
				case 1:
					ground = 8;
					supply = 14;
					break;
				case 2:
					ground = 6;
					supply = 13;
					break;
			}
			break;
	}
	data[0] = ground;
	data[1] = supply;
}
