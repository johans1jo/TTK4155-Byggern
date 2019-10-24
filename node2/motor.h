typedef enum Direction {
  RIGHT,
  LEFT
} direction_t;


void motor_init();
void motor_set_direction(direction_t dir);
void motor_enable();
void motor_disable();

void encoder_init();
int encoder_read();
void encoder_reset();
