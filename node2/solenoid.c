#include "microbit.h"
#include <avr/io.h>

#define X_PIN PF0
#define A_PIN PF1
#define B_PIN PF2

void microbit_init() {
	DDRF &= ~(1 << X_PIN)
	DDRF &= ~(1 << A_PIN)
	DDRF &= ~(1 << B_PIN);
}

int microbit_read_x() {
	return (PINF & (1 << X_PIN));
}

int microbit_read_a() {
	return (PINF & (1 << A_PIN));
}

int microbit_read_b() {
	return (PINF & (1 << B_PIN));
}
