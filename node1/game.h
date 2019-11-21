/**
 * @file
 * @brief Implementation of the game.
 */

 /**
  * @brief Sets mode to Clear Timer on Compare (CTC) mode. The counter is cleared to zero when the counter value
  * (TCNTn) matches either the OCRnA (WGMn3:0 = 4) or the ICRn (WGMn3:0 = 12).
  * Sets the Output Compare Pin OC3B to normal port operatoin
  * Sets the division factor for the prescaler to 1024.
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
 * @brief Returns the value game_on, equal to 1 when the game is on and 0 when it is not.
 *
 * @return game_on
 */
int game_is_on();

/**
 * @brief Sends a message struct with a mode-id to node 2, and enables timer-interrupt in order to send
 * data from the multifunction board.
 */
void game_play();

/**
 * @brief Disables timer-interrupt, sends a stop-message to node 2 and sets game_on = 0.
 */
void game_stop();

/**
 * @brief Enables Timer/Counter3 Output Compare B Match interrupt.
 */
void game_timer_enable();

/**
 * @brief Disables Timer/Counter3 Output Compare B Match interrupt.
 */
void game_timer_disable();

/**
 * @brief Sets the game difficulty by setting the parameters of the PI-controller.
 *
 * @param[in] The difficulty level.
 */
void game_set_difficulty(int difficulty);

/**
 * @brief Returns the user.
 *
 * @return user.
 */
int game_get_user();

/**
 * @brief Sets user to the input user_edit.
 *
 * @param[in] The new user.
 */
void game_choose_user(int new_user);

void game_edit_user(int user_edit);

/**
 * @brief Prints the score to the OLED.
 *
 * @param[in] The score.
 */
void game_show_fails(int fails);
void game_update_fails(int fails);

char * game_get_user_name(int user_id);
void game_set_user_name(int user_id, char * user_name);

void game_set_input_source(int new_input_source);
void game_send_everything();
void game_set_on();

#endif
