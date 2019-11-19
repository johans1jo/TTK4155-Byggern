/**
 * @file
 * @brief Implementation of the functions for the mode of the game.
 */

#ifndef MODE_H
#define MODE_H

typedef enum {
	NO_MODE = 0,
	MAIN_MENU,
  PLAY_GAME,
	SHOW_HIGHSCORE,
	EDIT_USER,
	CHOOSE_USER,
	CHOOSE_DIFFICULTY,
	SET_INPUT_SOURCE
} mode_t;

/**
 * @brief Sets the mode and the parameter.
 *
 * @param[in]
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
