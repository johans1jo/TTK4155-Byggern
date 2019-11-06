#define F_CPU 16000000UL

void controller_timer_init();
int controller(int reference, int encoder_value);
