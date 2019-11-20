/**
 * @file
 * @brief Implementation of the functions for the mode of the game.
 */

#ifndef MODE_H
#define MODE_H

typedef enum {
	MODE_IDLE = 0,
	MODE_MAIN_MENU,
  MODE_PLAY_GAME,
	MODE_SHOW_HIGHSCORE,
	MODE_EDIT_USER,
	MODE_CHOOSE_USER,
	MODE_CHOOSE_DIFFICULTY,
	MODE_SET_INPUT_SOURCE
} mode_t;

/**
 * @brief Sets the mode and the parameter.
 *
 * @param[in] The mode
 * @param[in] The parameter
 */
void mode_set(mode_t new_mode, int new_parameter);

/**
 * @brief Gets the current mode.
 *
 * @return The mode.
 */
mode_t mode_get();

/**
 * @brief Gets the current parameter.
 *
 * @return The parameter.
 */
int mode_parameter_get();

#endif
