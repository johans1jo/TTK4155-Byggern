/**
 * @file
 * @brief A driver for the SRAM.
 */

#include <stdlib.h>
#include <avr/io.h>
#include <stdio.h>

/**
 * @brief Initializes the SRAM by enabling XMEM and masking unused bits.
 */
void sram_init();

/**
 * @brief Writes data to a given address in the SRAM.
 *
 * @param[in] The adress.
 * @param[in] The data.
 */
void sram_write(uint16_t address, uint8_t data);

/**
 * @brief Writes the data on a given address in the SRAM.
 *
 * @param[in] The adress.
 *
 * @return The data.
 */
uint8_t sram_read(uint16_t address);
