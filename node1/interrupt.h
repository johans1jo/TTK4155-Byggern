/**
 * @file
 * @brief A driver for the interrupts.
 */

 /**
  * @brief Activates External Interrupt on Pin INT0 by
  * setting bit INT0 in the MCU Control Register.
  * Sets the interrupts to trigger on falling edge.
  * Sets Port D Pin 2 as input.
  */
void interrupt_init();
