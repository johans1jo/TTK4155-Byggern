#include <avr/io.h>

void oled_init();
void oled_write_command(uint8_t command);
void oled_write_data(uint8_t data);

void oled_goto_line(int line);
