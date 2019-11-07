#include "highscore.h"
#include "draw.h"

void highscore_show() {
	// Tegnegreier
	point points[] = {
		{0, 0},
		{10, 10},
		{50, 32}
	};
	draw_lines(points, sizeof(points)/sizeof(points[0]), 4);
	draw_print();
}
