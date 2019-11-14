void game_init();

void game_play();
void game_stop();
void game_pause();
void game_timer_enable();
void game_timer_disable();

int game_is_on();

void game_set_difficulty_hard();
void game_set_difficulty_medium();
void game_set_difficulty_easy();
void game_set_controller_parameters(int param_p, int param_i);

int game_get_user();
void game_set_user_0();
void game_set_user_1();
void game_set_user_2();
void game_set_user_3();
void game_set_user_4();

void game_show_score(int score);
