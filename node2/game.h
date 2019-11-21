/**
 * @file
 * @brief Implementation of the game.
 */

 /**
  * @brief Initializes the game.
  */

#ifndef GAME_H
#define GAME_H

enum {
	JOYSTICKS = 1,
	MICROBIT
};

enum {
	EASY,
	MEDIUM,
	HARD,
	CRAZY
};

void game_init();

/**
 * @brief Starts the game.
 */
void game_timer_init();

void game_timer_enable();

void game_timer_disable();

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
void game_set_input_source(int new_input_source);
void game_set_difficulty(int new_difficulty);
void game_clear_pause();
#endif
