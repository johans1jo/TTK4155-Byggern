#include "mode.h"

int mode = 0;

void mode_set(int m) {
	mode = m;
}

int mode_get() {
	return mode;
}
