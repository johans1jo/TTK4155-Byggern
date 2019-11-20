/**
 * @file
 * @brief Implementation of the servo.
 */

 /**
  * @brief Inputs an angle and sets the corresponding on-time for the PWM.
  *
  * @param[in] The angle.
  */
void servo_set_angle(double angle);

/**
 * @brief Inputs a joystick-value and sets the corresponding on-time for the PWM.
 *
 * @param[in] The joystick value.
 */
void servo_set_from_joystick(int y);

/**
 * @brief Converts from joystick value to degrees.
 *
 * @param[in] The joystick value.
 */
int joy_to_deg(int pos);
