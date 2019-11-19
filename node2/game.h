/**
 * @file
 * @brief Implementation of the game.
 */

 /**
  * @brief Initializes the game.
  */
void game_init();

/**
 * @brief Starts the game.
 */
void game_play();

/**
 * @brief Returns a boolean value depending on whether the game is on or not.
 *
 * @return The status.
 */
int game_is_on();

/**
 * @brief Sets the motor, servo, solenoid and ir.
 */
void game_set_everything();

/**
 * @brief Updates the game from node 1.
 *
 * @param[in] A pointer to the data.
 */
void game_update_from_node1(char* data);

//int game_is_goal();

/**
 * @brief Returns a boolean value depending on whether the game is initialized or not.
 *
 * @return The status.
 */
int game_is_initialized();

/**
 * @brief Stops.
 */
void game_stop();
