/**
 * @file
 * @brief A driver for the PWM.
 */

static unsigned int pwm_period;

/**
 * @brief Initializes the PWM.
 */
void pwm_init();

/**
 * @brief Sets the on-time of the duty cycle.
 *
 * @param[in] The on-time.
 */
void pwm_set_ms(double ms);
