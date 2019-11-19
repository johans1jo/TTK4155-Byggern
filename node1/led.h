/**
 * @file
 * @brief Functions to initialize, set and clear the LED.
 */


 /**
  * @brief Initializes the LED display by setting Port E Pin 0 to output.
  */
void led_init();

/**
 * @brief Sets the LED by setting Port E Pin 0 to logical high.
 */
void led_set();

/**
 * @brief Clears the LED by setting Port E Pin 0 to logical low.
 */
void led_clear();
void led_fire();
