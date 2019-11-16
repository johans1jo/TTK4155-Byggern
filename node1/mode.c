#include "mode.h"

mode_t mode = MAIN_MENU;
int parameter = 0;

void mode_set(mode_t new_mode, int new_parameter) {
	mode = new_mode;
	parameter = new_parameter;
}

mode_t mode_get() {
	return mode;
}

int mode_parameter_get() {
	return parameter;
}
