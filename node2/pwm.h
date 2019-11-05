static unsigned int pwm_period;

void pwm_init();
void pwm_set_ms(double ms);

void servo_set_angle(double angle);

int joy_to_deg(int pos);
