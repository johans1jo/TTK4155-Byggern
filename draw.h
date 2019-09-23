#ifndef HEI
#define HEI
unsigned char pixels[128][8];
void set_bit(int x, int y);
void print_pixels();

void draw_point(int x1, int y1, int size);
void draw_line(int x1, int y1, int x2, int y2, int size);

#endif
