#ifndef GAME_H
#define GAME_H

enum {
	JOYSTICKS = 1,
	MICROBIT
};

void game_init();
void game_play();
int game_is_on();
void game_set_everything();
void game_update_from_node1(char* data);
int game_is_initialized();

void game_stop();
void game_set_input_source(int new_input_source);

#endif
