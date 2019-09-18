#include <stdio.h>
#include "oled.h"

// MAX_SUBMENUS angir hvor mye plass i minnet som skal settes av til undermeny-array
#define MAX_SUBMENUS 10

// Menyelement
typedef struct Menu {
	char * text; // Teksten i menyelementet
	void (*function)(); // Funksjonen som skal kalles hvis det ikke finnes noen undermeny
	struct Menu * parent; // Pappameny :)
	struct Menu * subMenu[MAX_SUBMENUS]; // Undermeny. Array av pekere til menyelementer
} menu_t, *menu_ptr;

menu_t menu_init();
void menu_start(menu_ptr menu);
menu_ptr menu_goto(menu_ptr currentMenu, int depth, int element);
void menu_add_sub(menu_ptr menu, menu_ptr subMenu);

// Eksempelfunksjoner for testing
void t0();
void t0u0();
void t0u1();
void t0u2();
void t1();
void t2u0();

void highscore();
