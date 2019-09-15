#include "joystick.h"
#include <stdlib.h>

#define F_CPU 4915200
#include <util/delay.h>


uint8_t joy_x_min = 0;
uint8_t joy_x_max = 255;
uint8_t joy_y_min = 0;
uint8_t joy_y_max = 255;

volatile int x_offset;
volatile int y_offset;

uint8_t slide_left_V_min = 0;
uint8_t slide_left_V_max = 255;
uint8_t slide_right_V_min = 0;
uint8_t slide_right_V_max = 255;


//Compensates for natrual offset
int joy_auto_calibrate(){
  _delay_ms(1);
  x_offset = adc_read(JOYSTICK_X);

  _delay_ms(1);
  y_offset = adc_read(JOYSTICK_Y);
}

//Returns joystick X value between -100 and 100
int joy_read_x() {
  x_pos = (((adc_read(JOYSTICK_X)-x_offset)*200 )/ (joy_x_max - joy_x_min)) - 128;
  return 0;
}

//Returns joystick Y value between -100 and 100
int joy_read_y() {
  y_pos = (((adc_read(JOYSTICK_Y)-y_offset)*200 )/ (joy_y_max - joy_y_min)) - 128;
  return 0;
}

int joy_dir() {
  int x = joy_read_x();
  int y = joy_read_y();
  //If X direction has largest value
  if (abs(x_pos) > abs(y_pos)) {
    if (x > 80) {
      return RIGHT;
    }
    else if (x < 80) {
      return LEFT;
    }
    else {
      return 0;
    }
  }
  //If Y direction has largest value
    if (abs(y_pos) > abs(x_pos)) {
    if (y > 80) {
      return UP;
    }
    else if (y < 80) {
      return DOWN;
    }
    else {
      return 0;
    }
  }
  return 0;
}
