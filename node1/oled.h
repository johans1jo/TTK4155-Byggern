#ifndef OLED_H
#define OLED_H
/**
 * @file
 * @brief A driver for the OLED display.
 */

#include <avr/io.h>

/**
 * @brief Initializes the display.
 */
void oled_init();

/**
 * @brief Writes a command.
 *
 * @param[in] The command.
 */
void oled_write_command(uint8_t command);

/**
 * @brief Writes data to the display.
 *
 * @param[in] The data.
 */
void oled_write_data(uint8_t data);

/**
 * @brief Goes to the desired line on the display.
 *
 * @param[in] The line.
 */
void oled_goto_line(int line);

/**
 * @brief Goes to the desired column on the display.
 *
 * @param[in] The column.
 */
void oled_goto_column(int column);

/**
 * @brief Goes to the desired position on the display.
 *
 * @param[in] The line.
 * @param[in] The column.
 */
void oled_goto_pos(int line, int column);

/**
 * @brief Goes to the origin position on the dispay.
 */
void oled_goto_home();

/**
 * @brief Clears a desired line on the display.
 *
 * @param[in] The line.
 */
void oled_clear_line(int line);

/**
 * @brief Clears the display.
 */
void oled_clear();

/**
 * @brief Clears resets the display by clearing it and setting the poisition
 * to the origin.
 */
void oled_reset();

/**
 * @brief Sets all LED-bits of the display.
 */
void oled_fill();

/**
 * @brief Prints a character on the display.
 *
 * @param[in] The character.
 */
void oled_print_char(char c);

/**
 * @brief Prints a string on the display.
 *
 * @param[in] The string.
 */
 void oled_print(const char c[]);
 void oled_print_pgm(const char word_pointer[]);

 #endif
