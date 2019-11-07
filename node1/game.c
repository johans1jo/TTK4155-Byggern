#include "game.h"
#include "can.h"
#include "mode.h"

void game_play() {
	message_t mode_msg = {
		100, //Mode-id
		1,
		GAME
	};
	can_send(&mode_msg);

	// Start sendetimer
}
