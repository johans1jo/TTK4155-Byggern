#include "game.h"
#include "can.h"
#include "mode.h"

void game_play() {
		printf("Sender CAN-mode-melding\r\n");

		message_t mode_msg = {
			100, //Mode-id
			1,
			GAME
		};
		can_send(&mode_msg);
		_delay_ms(100);

		printf("Sender multifunkverdier\r\n");
	  while (1) {
			can_send_everything();
	    _delay_ms(100);
	  }
}
