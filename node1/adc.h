#include <avr/io.h>

#ifndef ADC
#define ADC

enum {
    JOYSTICK_Y = 1,
    JOYSTICK_X,
    SLIDER_LEFT,
    SLIDER_RIGHT
};

void adc_init();
int adc_read(int channel);

#endif
