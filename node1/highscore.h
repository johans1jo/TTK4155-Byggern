/**
 * @file
 * @brief Implementation of the highscore-function.
 */

 /**
  * @brief Shows the highscore of the current user on the OLED.
  */
void highscore_show();

/**
 * @brief Saves the highscore of the current user.
 *
 * @param[in] The score.
 *
 * @param[in] The user.
 */
void highscore_save(int score, int user);
