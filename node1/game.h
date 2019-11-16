void game_init();
int game_is_on();

void game_play();
void game_stop();
void game_pause();
void game_timer_enable();
void game_timer_disable();

void game_set_difficulty(int difficulty);
void game_set_controller_parameters(int param_p, int param_i);

int game_get_user();
void game_choose_user(int new_user);
void game_edit_user(int user_edit);

void game_show_score(int score);

char * game_get_user_name(int user_id);
void game_set_user_name(int user_id, char * user_name);
