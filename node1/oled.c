#include "oled.h"
#include <string.h>
#include "uart.h"
#include <avr/pgmspace.h>
#include "fonts.h"
#include "draw.h"
#include <avr/pgmspace.h>

//int oled_write = 0;

void oled_init() {
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

 // Page addressing mode
	oled_write_command(0x20);
	oled_write_command(0b10);
}

void oled_write_command(uint8_t command) {
  volatile char *ext_oled_command = (char *) 0x1000;
  ext_oled_command[0] = command;
}

void oled_write_data(uint8_t data) {
	////printf("ow %d\r\n", oled_write);
	//oled_write++;
  volatile char *ext_oled_data = (char *) 0x1200;
  ext_oled_data[0] = data;
}

void oled_goto_line(int line) { //Line between 0-7
  int command = 0xB0 + line;
  oled_write_command(command);

}

void oled_goto_column(int column) {
	  oled_write_command(0x00 + (column % 16)); // Lower nibble
	  oled_write_command(0x10 + (column / 16)); // Higher nibble
}

void oled_goto_pos(int line, int column) {
  oled_goto_line(line);
  oled_goto_column(column);
}


void oled_goto_home() {
  oled_goto_pos(0,0);
}

void oled_clear_line(int line) {
  oled_goto_line(line);
  oled_goto_column(0);
  for (int i=0; i<128; i++) {
    oled_write_data(0x00);
  }
}

void oled_clear() {
  for (int i=0; i < 8; i++) {
    oled_clear_line(i);
  }
}

void oled_reset() {
  oled_clear();
  oled_goto_home();
}

void oled_fill() {
  for (int i=0; i < 8; i++) {
    oled_goto_line(i);
    oled_goto_column(0);
    for (int j=0; j<128; j++) {
      oled_write_data(0xFF);
    }
  }
}

void oled_print_char(char c) {
  c = c-32;
  for (int i = 0; i < 7; i++) {
    int hei = pgm_read_byte(&font8[c][i]);
    oled_write_data(hei);
  }
}

void oled_print(const char c[]) {
  for (int i = 0; i < strlen(c); i++) {
    oled_print_char(c[i]);
  }
}

void oled_print_pgm(const char word_pointer[]) {
	  char word[30];
	  strcpy_P(word,word_pointer);
		oled_print(word);
}
