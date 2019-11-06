/**
 * @file
 * @brief A driver for the joystick containing functions to read and send values from the joystick
 */

#include "adc.h"

typedef enum {
    RIGHT = 1,
    LEFT,
    UP,
    DOWN
} joystick_dir_t;

volatile int x_pos;
volatile int y_pos;

/**
 * @brief Calibrates the joystick to find the offset needed to compensate for
 */
int joy_calibrate();

/**
 * @brief Reads the value for the x-position from the joystick
 *
 * @return The x-position from the joystick
 */
int joy_read_x();

/**
 * @brief Reads the value for the y-position from the joystick
 * @return The y-position from the joystick
 */
int joy_read_y();

/**
 * @brief Determines the direction of the joystick, based on the values read from the joystick.
 * @return The direction of the joystick, either UP, DOWN, RIGHT or LEFT.
 */
int joy_read_dir();

/**
 * @brief Sends the position of the joystick over CAN.
 */
void joy_send_coordinates();

/**
 * @brief A get-function for the x-offset of the joystick
 * @return The x-offset
 */
int getxoffset();

/**
 * @brief A get-function for the y-offset of the joystick
 * @return The y-offset
 */
int getyoffset();

/**
 * @brief Converts the joystick-value to degrees
 * @return The joystick-value in degrees
 */
int joy_to_deg(int pos);
