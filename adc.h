#include <avr/io.h>

enum {
    JOYSTICK_X = 1,
    JOYSTICK_Y,
    SLIDER_LEFT,
    SLIDER_RIGHT
};

void adc_init();
int adc_read(int channel);
