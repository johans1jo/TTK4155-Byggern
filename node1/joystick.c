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

//Compensates for natrual offset
int joy_calibrate(){
  x_offset = adc_read(JOYSTICK_X);
  y_offset = adc_read(JOYSTICK_Y);
}

//Returns joystick X value between -100 and 100
int joy_read_x() {
  //x_pos = (((adc_read(JOYSTICK_X)-x_offset)*200 )/ (joy_x_max - joy_x_min)) - 128;
  //return 0;
  //int pos = (adc_read(JOYSTICK_X)-x_offset) * 100 / 127;
  int pos = (adc_read(JOYSTICK_X) - x_offset) * 100 / 127;
  int offset = 127 - x_offset; //2
  if (pos > 0) {
    pos = pos * 100 / (100 + offset);
  } else if (pos < 0) {
    pos = pos * 100 / (100 - offset);
  }
  return pos;
}

//Returns joystick Y value between -100 and 100
int joy_read_y() {
  //y_pos = (((adc_read(JOYSTICK_Y)-y_offset)*200 )/ (joy_y_max - joy_y_min)) - 128;
  //return 0;
  //int pos = (adc_read(JOYSTICK_Y)-y_offset) * 100 / 127;
  int pos = (adc_read(JOYSTICK_Y) - y_offset) * 100 / 127;
  int offset = 127 - y_offset; //-11
  if (pos > 0) {
    pos = pos * 100 / (92); //jalla
  } else if (pos < 0) {
    pos = pos * 100 / (106); //jalla
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
  /*
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
  */
}

void joy_send_coordinates() {
		printf("send joystickkoordinater...\r\n");
		while (1) {
			int x = joy_read_x();
			message_t x_coordinate = {
				10,
				3,
				x
			};
			can_send(&x_coordinate);

			int y = joy_read_y();
			message_t y_coordinate = {
				11,
				3,
				y
			};
			can_send(&y_coordinate);

			_delay_ms(1000);
		}
}
