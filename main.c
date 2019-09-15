#include <avr/io.h>
#include "uart.h"
#include "joystick.h"

#define F_CPU 4915200
#include <util/delay.h>

#include "oled.h"
#include <string.h>

#define FOSC 4915200// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


int main(void){
    uart_init ( MYUBRR );
    adc_init();
    joy_calibrate();

    oled_init();
    oled_clear();

    oled_goto_pos(3,10);
    oled_print("x: ");
    oled_goto_pos(5,10);
    oled_print("y: ");

    while (1) {
      int dir = joy_read_dir();
      oled_goto_pos(1,10);
      switch(dir) {
        case UP:
          oled_print("Opp");
          break;
        case DOWN:
          oled_print("Ned");
          break;
        case RIGHT:
          oled_print("Hoyre");
          break;
        case LEFT:
          oled_print("Venstre");
          break;
      }
      
      _delay_ms(1000);
    }

    return 0;
}
