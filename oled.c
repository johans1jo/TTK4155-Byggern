#include "oled.h"

void oled_init()
 {
 oled_write_command(0xae); // display off
 oled_write_command(0xa1); //segment remap
 oled_write_command(0xda); //common pads hardware: alternative
 oled_write_command(0x12);
 oled_write_command(0xc8); //common output scan direction:com63~com0
 oled_write_command(0xa8); //multiplex ration mode:63
 oled_write_command(0x3f);
 oled_write_command(0xd5); //display divide ratio/osc. freq. mode
 oled_write_command(0x80);
 oled_write_command(0x81); //contrast control
 oled_write_command(0x50);
 oled_write_command(0xd9); //set pre-charge period
 oled_write_command(0x21);
 oled_write_command(0x20); //Set Memory Addressing Mode
 oled_write_command(0x02);
 oled_write_command(0xdb); //VCOM deselect level mode
 oled_write_command(0x30);
 oled_write_command(0xad); //master configuration
 oled_write_command(0x00);
 oled_write_command(0xa4); //out follows RAM content
 oled_write_command(0xa6); //set normal display
 oled_write_command(0xaf); // display on
}

void oled_write_command(uint8_t command) {
  volatile char *ext_oled_command = (char *) 0x1000;
  ext_oled_command[0] = command;
}

void oled_write_data(uint8_t data) {
  volatile char *ext_oled_data = (char *) 0x1200;
  ext_oled_data[0] = data;
}

void oled_goto_line(int line) {
  int command = 0xB0 + line;
  oled_write_command(command);
}
