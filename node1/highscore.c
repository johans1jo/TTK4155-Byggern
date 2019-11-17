#include "highscore.h"
#include "draw.h"
#include "oled.h"
#include "menu.h"
#define F_CPU 4915200
#include <util/delay.h>

#define HIGHSCORE_SIZE 5

int highscore[HIGHSCORE_SIZE] = {0};

void highscore_show() {
	// Graph width per user.
	int width = 128/(HIGHSCORE_SIZE-1);
	// Find highest highscore (heh).
	int highest_score = 0;
	for (int i = 0; i < HIGHSCORE_SIZE; i++) {
		if (highscore[i] > highest_score) {
			highest_score = highscore[i];
		}
	}

	// Draw the graph!
	point points[HIGHSCORE_SIZE] = {0};
	for (int i = 0; i < HIGHSCORE_SIZE; i++) {
		points[i].x = width*i;
		int score_mapped = (highscore[i]*50/highest_score);
		points[i].y = 63 - score_mapped;
		if (highscore[i] == highest_score && highest_score != 0) {
			draw_circle(points[i].x, points[i].y, 20, 2);
		}
	}
	draw_lines(points, sizeof(points)/sizeof(points[0]), 2);

	draw_push();
}

void highscore_save(int score, int user) {
	highscore[user] = score;
}
