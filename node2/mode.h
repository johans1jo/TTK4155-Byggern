/**
 * @file
 * @brief Implementation of the functions for the mode of the game.
 */

typedef enum {
	MODE_IDLE = 0,
	MODE_MAIN_MENU,
	MODE_PLAY_GAME,
	MODE_SHOW_HIGHSCORE,
	MODE_EDIT_USER,
	MODE_CHOOSE_USER,
	MODE_CHOOSE_DIFFICULTY,
	MODE_SET_INPUT_SOURCE,
	MODE_STOP_GAME
} mode_t;

/**
 * @brief Sets the mode and the parameter.
 *
 * @param[in] The mode
 */
void mode_set(int m);

/**
 * @brief Gets the current mode.
 *
 * @return The mode.
 */
int mode_get();
