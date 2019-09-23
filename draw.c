#include "draw.h"
#include <stdio.h>

unsigned char pixels[128][8] = { 0 };


// Tegner linje fra punktet (x1, y1) til punktet (x2, y2)
void draw_line(int x1, int y1, int x2, int y2, int size) {
	for (int x = x1; x < x2; x++) {
		int s = (y2 - y1)*1000 / (x2 - x1);
		int y = y1 + (s*(x - x1)) / 1000;
		printf(".%d", y);
		draw_point(x, y, size);
	}
}

// Tegn et punkt med gitt tykkelse
void draw_point(int x1, int y1, int size) {
	if (size == 0) {
		return;
	}
	set_bit(x1, y1);

	if (size > 1) {

		int oneLess = !(size % 2);
		int x_low   = x1 - (size / 2) + oneLess;
		int x_high  = x1 + (size / 2);
		int y_low   = y1 - (size / 2) + oneLess;
		int y_high  = y1 + (size / 2);

		for (int y = y_low; y <= y_high; y++) {
			for (int x = x_low; x <= x_high; x++) {
				draw_point(x, y, 1);
			}
		}

	}
}

void set_bit(int x, int y) {
	int line = y/8;
	int bit = y%8;
	pixels[x][line] |= (1 << bit);
}

void print_pixels() {
	//oled
}
