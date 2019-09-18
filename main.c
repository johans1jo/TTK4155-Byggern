#include <avr/io.h>
#include "uart.h"
#include "joystick.h"

#define F_CPU 4915200
#include <util/delay.h>

#include "oled.h"
#include <string.h>
#include "menu.h"
#include "spi.h"
#include "MCP2515.h"
#include <avr/interrupt.h>
_SEI();

#define FOSC 4915200// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


int main(void){
    uart_init ( MYUBRR );
    adc_init();
    joy_calibrate();

    oled_init();
		oled_clear();

		_delay_ms(1000);

		spi_master_init();

		//SS aka CS lav
		DDRB = (1 << PB4);
		PORTB = (0 << PB4);

		//Loopback
		spi_master_transmit(0b101);
		printf("1");
		spi_master_transmit(MCP_CANCTRL);
		printf("2");
		spi_master_transmit(MODE_LOOPBACK);
		printf("3");
		spi_master_transmit(MODE_LOOPBACK);
		printf("4");

		char transmitChar = 6;

		// SS høy
		PORTB = (1 << PB4);
		_delay_ms(100);
		PORTB = (0 << PB4);

		spi_master_transmit(0b10);
		printf("5");
		spi_master_transmit(transmitChar);
		printf("6");



		spi_slave_init();
		char receiveChar = spi_slave_receive();
		printf("%c", receiveChar);


/*

		PORTB = (0 << PB4);

		menu_t menu = menu_init();
		menu_start(&menu);



    while (1) {
			oled_clear();
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

		*/

    return 0;
}
