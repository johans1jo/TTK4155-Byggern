/**
 * @file
 * @brief A driver for the encoder.
 */

 /**
  * @brief Initializes the encoder.
  *
  */
void encoder_init();

/**
 * @brief Resets the encoder.
 *
 */
void encoder_reset();

/**
 * @brief Calibrates the encoder.
 *
 */
void encoder_calibrate();

/**
 * @brief Reads the value from the encoder.
 *
 */
int encoder_read();

/**
 * @brief Returns an encoder-value relative to the given reference.
 *
 */
int encoder_map(int reference);
