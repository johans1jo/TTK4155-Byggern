#ifndef HEI
#define HEI

// Linje
typedef struct Point {
	int x;
	int y;
} point;


void draw_set_bit(int x, int y);
void draw_clear_bit(int x, int y);
void draw_print();
void draw_init();
void draw_clear();

void draw_point(int x1, int y1, int size);
void draw_circle(int x1, int y1, int width, int size);
void draw_line(int x1, int y1, int x2, int y2, int size);
void draw_lines(point * points, int length, int size);

#endif
