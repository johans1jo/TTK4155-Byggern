#include <avr/io.h>

void oled_init();
void oled_write_command(uint8_t command);
void oled_write_data(uint8_t data);
void oled_goto_line(int line);
void oled_goto_column(int column);
void oled_goto_pos(int line, int column);
void oled_goto_home();
void oled_clear_line(int line);
void oled_clear();
void oled_reset();
void oled_fill();
