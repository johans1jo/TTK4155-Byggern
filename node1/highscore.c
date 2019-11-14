#include "highscore.h"
#include "draw.h"
#include "oled.h"

int highscore = 0;

void highscore_show() {
	// Tegnegreier
	/*
	point points[] = {
		{0, 0},
		{10, 10},
		{50, 32}
	};
	draw_lines(points, sizeof(points)/sizeof(points[0]), 4);
	draw_print();
	*/
	oled_clear();
	oled_goto_pos(10,10);
	char score_char[1];
	sprintf(score_char, "%d", highscore);
	oled_print(score_char);
}

void highscore_save(int score) {
	highscore = score;
}
