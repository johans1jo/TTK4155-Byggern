#include "draw.h"
#include "sram.h"
#include "oled.h"
#include <stdio.h>

void draw_init() {
	draw_clear();
}

// Tegner linje fra punktet (x1, y1) til punktet (x2, y2) med størrelse size
void draw_line(int x1, int y1, int x2, int y2, int size) {
	if (x1 > x2) {
		int tmp = x1;
		x1 = x2;
		x2 = tmp;
	}
	if (y1 > y2) {
		int tmp = y1;
		y1 = y2;
		y2 = tmp;
	}
		for (int x = x1; x < x2; x++) {
			int s = (y2 - y1)*1000 / (x2 - x1);
			int y = y1 + (s*(x - x1)) / 1000;
			draw_point(x, y, size);
		}
}

void draw_lines(point * points, int length, int size) {
	for (int i = 0; i < length - 1; i++) {
		printf("x %d y %d\r\n", points[i+1].x, points[i+1].y);
		draw_line(points[i].x, points[i].y, points[i+1].x, points[i+1].y, size);
	}
}

void draw_circle(int x1, int y1, int width, int size) {
	//(x−h)2+(y−k)2=r2
}

// Tegner et punkt på posisjon (x1, y1) med størrelse size
void draw_point(int x1, int y1, int size) {
	if (size == 0) {
		return;
	}
	draw_set_bit(x1, y1);

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

void draw_set_bit(int x, int y) {
	int line = y/8;
	int bit = y%8;
	//pixels[x][line] |= (1 << bit);

	int address = x*8 + line;
	char byte = sram_read(address);

	byte |= (1 << bit);

	sram_write(address, byte);
	char byte2 = sram_read(address);
}

void draw_clear_bit(int x, int y) {
	int line = y/8;
	int bit = y%8;

	int address = x*8 + line;
	char byte = sram_read(address);

	byte &= ~(1 << bit);

	sram_write(address, byte);
	char byte2 = sram_read(address);
}

void draw_clear() {
	for (int address = 0; address < 128*8; address++) {
		sram_write(address, 0);
	}
}

void draw_print() {
	for (int x = 0; x < 128; x++) {
		for (int line = 0; line < 8; line++) {
			int address = x*8 + line;
			char byte = sram_read(address);
			oled_goto_pos(line, x);
			oled_write_data(byte);
		}
	}
}