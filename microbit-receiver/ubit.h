#ifndef UBIT_H
#define UBIT_H

void ubit_led_matrix_init();

void ubit_led_matrix_turn_on();

void ubit_led_matrix_turn_off();


void ubit_buttons_init();

int ubit_button_press_a();

int ubit_button_press_b();


void ubit_uart_init();

void ubit_uart_print(char * p_format, ...);

#endif
