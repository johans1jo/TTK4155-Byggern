/**
 * @file
 * @brief A driver for the motor.
 */

typedef enum Direction {
  RIGHT,
  LEFT
} direction_t;

/**
 * @brief Initializes the motor.
 */
void motor_init();

/**
 * @brief Sets mode to Clear Timer on Compare (CTC) mode. The counter is cleared to zero when the counter value
 * (TCNTn) matches either the OCRnA (WGMn3:0 = 4) or the ICRn (WGMn3:0 = 12).
 * Sets the Output Compare Pin OC3B to normal port operatoin
 * Sets the division factor for the prescaler to 1024.
 * OCR3B is continuously compared with counter (TCNT1).
 * Enables timer 3 interrupt, compare match
 */
void motor_controller_init();

/**
 * @brief Enables the motor.
 */
void motor_enable();

/**
 * @brief Disables the motor.
 */
void motor_disable();

/**
 * @brief Sets the direction of the motor.
 *
 * @param[in] The direction.
 */
void motor_set_direction(direction_t dir);

/**
 * @brief Sets the speed of the motor.
 *
 * @param[in] The speed of the motor.
 */
void motor_set_speed(int speed);

/**
 * @brief Sets the position of the motor to a reference position.
 *
 * @param[in] The reference position.
 */
void motor_set_position(int reference);

/**
 * @brief Sets the parameters of the controller of the motor.
 *
 * @param[in] The K_p parameter of the controller.
 * @param[in] The K_i parameter of the controller.
 */
void motor_set_controller_parameters(int param_p, int param_i);

/**
 * @brief Gets the K_p of the controller of the motor.
 *
 * @param[in] The K_p parameter.
 */
int motor_get_controller_parameter_p();

/**
 * @brief Gets the K_i of the controller of the motor.
 *
 * @param[in] The K_i parameter.
 */
int motor_get_controller_parameter_i();
