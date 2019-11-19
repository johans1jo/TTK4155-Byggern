#include "highscore.h"
#include "draw.h"
#include "oled.h"
#include "menu.h"
#define F_CPU 4915200
#include <util/delay.h>

#define HIGHSCORE_SIZE 5

int highscore[HIGHSCORE_SIZE] = {0,3,5,0,0};

void highscore_show() {
	oled_clear();
	draw_clear();
	// Bredden på grafen per bruker
	int width = 128/(HIGHSCORE_SIZE-1);
	// Finner høyeste poengsum
	int highest_score = 0;
	for (int i = 0; i < HIGHSCORE_SIZE; i++) {
		if (highscore[i] > highest_score) {
			highest_score = highscore[i];
		}
	}

	// Tegner grafen :)
	point points[HIGHSCORE_SIZE] = {0};
	for (int i = 0; i < HIGHSCORE_SIZE; i++) {
		points[i].x = width*i;
		int score_mapped = (highscore[i]*40/highest_score);
		points[i].y = 63 - score_mapped;
		if (highscore[i] == highest_score && highest_score != 0) {
			draw_circle(points[i].x, points[i].y, 20, 2);
		}
	}
	draw_lines(points, sizeof(points)/sizeof(points[0]), 2);

	draw_push();

	// Drar fram "til hovedmeny"-menyen
	//menu_ptr menu_highscore = menu_init(HIGHSCORE);
	//menu_start(menu_highscore, DONT_CLEAR);
}

void highscore_save(int score, int user) {
	//printf("highscore user %d score %d\r\n", user, score);
	highscore[user] = score;
}
