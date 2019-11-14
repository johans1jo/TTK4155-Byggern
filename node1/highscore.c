#include "highscore.h"
#include "draw.h"
#include "oled.h"
#include "menu.h"
#define F_CPU 4915200
#include <util/delay.h>

#define HIGHSCORE_SIZE 2

//int highscore[10] = {0};
int highscore[HIGHSCORE_SIZE] = {10,0};

void highscore_show() {
	// Tegnegreier

	/*
	point points[] = {
		{0, 0},
		{10, 10},
		{50, 32}
	};
	*/
	/*
	draw_lines(points, sizeof(points)/sizeof(points[0]), 4);
	draw_print();
	*/
	int width = 128/(HIGHSCORE_SIZE-1);

	point points[HIGHSCORE_SIZE] = {0};
	for (int i = 0; i < HIGHSCORE_SIZE; i++) {
		points[i].x = width*i;
		points[i].y = highscore[i];
	}
	/*
	point a = {10, 10};
	point b = {20, 20};
	draw_line(0, 0, 10, 33, 1);
*/
	//draw_lines(points, sizeof(points)/sizeof(points[0]), 2);

	//printf("\r\n\r\n\r\n");
	draw_line(0, 10, 10, 0, 1);
	draw_print();
	while(1) {
		_delay_ms(100);
	}
	/*
	oled_goto_pos(10,10);
	char score_char[1];
	sprintf(score_char, "%d", highscore);
	oled_print(score_char);

	menu_ptr menu_highscore = menu_init(HIGHSCORE);
	menu_start(menu_highscore, DONT_CLEAR);
	*/
}

void highscore_save(int score) {
	highscore[0] = score;
}
