#include "adc.h"

typedef enum {
	RIGHT = 1,
	LEFT,
	UP,
	DOWN
} joystick_dir_t;

volatile int x_pos;
volatile int y_pos;

int joy_calibrate();
int joy_read_x();
int joy_read_y();
int joy_read_dir();

int getxoffset();
int getyoffset();
