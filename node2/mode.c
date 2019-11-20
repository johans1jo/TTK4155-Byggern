#include "mode.h"

int mode = MODE_IDLE;

void mode_set(int m) {
	mode = m;
}

int mode_get() {
	return mode;
}
