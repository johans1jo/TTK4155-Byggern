/**
 * @file
 * @brief Implementation of the functions for the mode of the game.
 */

enum {
	IDLE = 0,
  GAME = 1
};

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
