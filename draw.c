#include "draw.h"
#include "oled.h"

// Tegner linje fra punktet (x1, y1) til punktet (x2, y2)
void draw_line(int x1, int y1, int x2, int y2) {
	int line = y1 / 8;
	int bit = y1 % 8;
	int column = x1;
	oled_goto_line(line);
	oled_goto_column(column);
	oled_write_data()
}

/*
// Tegn et punkt med gitt tykkelse
void draw_point(int x1, int y1) {
	int line = y1 / 8;
	int bit = y1 % 8;
	char byte = 0x00 (1 << bit);
	int column = x1;
	oled_goto_line(line);
	oled_goto_column(column);
	oled_write_data(byte);
}
*/

// Tegn et punkt med gitt tykkelse
void draw_point(int x1, int y1, int size) {
	if (size == 0) {
		return;
	}
	int line = y1 / 8;
	int bit = y1 % 8;
	char byte = 0x00 (1 << bit);
	int column = x1;
	oled_goto_line(line);
	oled_goto_column(column);
	oled_write_data(byte);

	if (size > 1) {

		int oneLess= !(size % 2)
		int x_low  = x1 - (size / 2) + oneLess;
		int x_high = x1 + (size / 2);
		int y_low  = y1 - (size / 2) + oneLess;
		int y_high = y1 + (size / 2);

		char byte  = 0x00
		for (int y = y_low; y <= y_high; y++) {
		}

		for (int x = x_low; x <= x_high; x++) {
			draw_point(x, y, 1);
		}

	}
}
