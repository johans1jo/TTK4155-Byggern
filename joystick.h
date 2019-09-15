#include "adc.h"

typedef enum {
    RIGHT = 1,
    LEFT,
    UP,
    DOWN
} joystick_dir_t;

volatile int x_pos;
volatile int y_pos;


int joy_autocalibrate();
int joy_read_x();
int joy_read_y();
int joy_dir();