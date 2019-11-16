typedef enum Direction {
  RIGHT,
  LEFT
} direction_t;

void motor_init();
void motor_controller_init();
void motor_enable();
void motor_disable();
void motor_set_direction(direction_t dir);
void motor_set_speed(int speed);
void motor_set_position(int reference);

void motor_set_controller_parameters(int param_p, int param_i);
int motor_get_controller_parameter_p();
int motor_get_controller_parameter_i();
