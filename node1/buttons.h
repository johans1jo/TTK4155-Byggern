/**
 * @file
 * @brief Initializes the buttons on the USB multifunction board
 */

#define JOYSTICK_BUTTON_PIN DDB0
#define LEFT_BUTTON_PIN DDB1
#define RIGHT_BUTTON_PIN DDB2


/**
 * @brief Initializes the joystick button and the left and right buttons by
 * assigning them to respictively Port B Pin 0, 1 and 2
 */
void buttons_init();

/**
 * @brief Reads the value on Port B Pin 0.
 *
 * @return The value on Port B Pin 0.
 */
int buttons_joystick();

/**
 * @brief Reads the value on Port B Pin 1.
 *
 * @return The value on Port B Pin 1.
 */
int buttons_left();

/**
 * @brief Reads the value on Port B Pin 2.
 *
 * @return The value on Port B Pin 2.
 */
int buttons_right();
