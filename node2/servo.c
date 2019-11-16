#include "servo.h"
#include "pwm.h"

void servo_set_angle(double angle) {
  angle = (angle + 30) * 1.8;
  double ms = 1.5 + (0.5 / 90.0) * angle;
  pwm_set_ms(ms);
}

void servo_set_from_joystick(int y) {
	int angle = joy_to_deg(y);
	servo_set_angle(angle);
}

int joy_to_deg(int pos) {
  return pos * 90 / 100;
}
