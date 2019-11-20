/**
 * @file
 * @brief A driver for the ADC.
 */


 /**
  * @brief Initializes the ADC. Selects AVCC with external capacitor at AREF pin
  * as Voltage Reference.
  * Selects single-ended at PIN ADC2.
  * Enables ADC, and sets the division factor for the prescaler to 128.
  */
void adc_init();

/**
 * @brief Reads the value from the ADC.
 *
 * @return The value from the ADC.
 */
int adc_read();
