#define JOYSTICK_BUTTON_PIN DDB0
#define LEFT_BUTTON_PIN DDB1
#define RIGHT_BUTTON_PIN DDB2

void buttons_init();
int buttons_joystick();
int buttons_left();
int buttons_right();
