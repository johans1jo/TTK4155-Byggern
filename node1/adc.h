/**
*@file
*@brief A driver for the adc containing functions to initialize the adc and read the data from the joystick
*/

#include <avr/io.h>

enum {
    JOYSTICK_Y = 1,
    JOYSTICK_X,
    SLIDER_LEFT,
    SLIDER_RIGHT
};

/**
 @brief Sets the SRE-bit in the MCU Control Register (MCUCR) to enable External Memory Interface. Releases Port C Pin 7-4 for normal Port Pin function.
 */
void adc_init();

/**
 @brief Allocates the adress space of the ADC to begin at base address Ox1400 in the External Memory space. Creates a pointer to the base address, and reads the value from the memory address.
 
 @param[in] channel The channel from the ADC
 
 @return The value read from the joystick 
 */
int adc_read(int channel);
