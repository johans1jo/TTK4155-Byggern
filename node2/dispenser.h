enum {
	CLEAR_DISPENSER,
	DROP_BALL
};

void dispenser_open();
void dispenser_close();
void dispenser_clear();
void dispenser_clear_hard();
void dispenser_select_top();
void dispenser_select_bottom();
void dispenser_drop_ball(int new_pre_time);
void dispenser_init();
void dispenser_start_timer();
void dispenser_stop_timer();
void dispenser_do();
