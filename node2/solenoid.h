/**
 * @file
 * @brief A driver for the solenoid.
 */

 /**
  * @brief Initializes the solenoid.
  */
void solenoid_init();

/**
 * @brief Sets the solenoid.
 */
void solenoid_set();

/**
 * @brief Clears the solenoid.
 */
void solenoid_clear();

/**
 * @brief Checks if the solenoid is set.
 *
 * @return A boolean corresponding to if the solenoid is set or not.
 */
int solenoid_is_set();

/**
 * @brief Fires the solenoid.
 */
void solenoid_fire();
