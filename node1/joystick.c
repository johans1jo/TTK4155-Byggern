#include "joystick.h"
#include <stdlib.h>
#include "uart.h"
#include "can.h"

#define F_CPU 4915200
#include <util/delay.h>

int joy_x_min = 0;
int joy_x_max = 255;
int joy_y_min = 0;
int joy_y_max = 255;

volatile int x_offset = 125;
volatile int y_offset = 125;

int slide_left_V_min = 0;
int slide_left_V_max = 255;
int slide_right_V_min = 0;
int slide_right_V_max = 255;

int getxoffset() {
  return x_offset;
}
int getyoffset() {
  return y_offset;
}

//Compensate for natrual offset
int joy_calibrate(){
  x_offset = adc_read(JOYSTICK_X);
  y_offset = adc_read(JOYSTICK_Y);
}

//Return joystick X value between -100 and 100
int joy_read_x() {
  int pos = (adc_read(JOYSTICK_X) - x_offset) * 100 / 127;
  int offset = 127 - x_offset;
  if (pos > 0) {
    pos = pos * 100 / (100 + offset);
  } else if (pos < 0) {
    pos = pos * 100 / (100 - offset);
  }
  return pos;
}

//Return joystick Y value between -100 and 100
int joy_read_y() {
  int pos = (adc_read(JOYSTICK_Y) - y_offset) * 100 / 127;
  int offset = 127 - y_offset;
  if (pos > 0) {
    pos = pos * 100 / (92);
  } else if (pos < 0) {
    pos = pos * 100 / (106);
  }
  return pos;
}

int joy_read_dir() {
  int x = joy_read_x();
  int y = joy_read_y();
  if (x > 70 && y < 70 && y > -70) {
    return UP;
  } else if (x < -70 && y < 70 && y > -70) {
    return DOWN;
  } else if (y > 70 && x < 70 && x > -70) {
    return RIGHT;
  } else if (y < -70 && x < 70 && x > -70) {
    return LEFT;
  } else {
    return 0;
  }
}
