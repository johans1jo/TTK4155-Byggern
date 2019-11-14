#include <stdio.h>
#include "oled.h"

// MAX_SUBMENUS angir hvor mye plass i minnet som skal settes av til undermeny-array
#define MAX_SUBMENUS 3

typedef enum {
	MAIN,
	IN_GAME,
	HIGHSCORE
} menu_type_t;

enum {
	DONT_CLEAR = 0,
	CLEAR
};

// Menyelement
typedef struct Menu {
	char * text; // Teksten i menyelementet
	void (*function)(); // Funksjonen som skal kalles hvis det ikke finnes noen undermeny
	struct Menu * parent; // Pappameny :)
	struct Menu * subMenu[MAX_SUBMENUS]; // Undermeny. Array av pekere til menyelementer
} menu_t, *menu_ptr;

menu_ptr menu_init(menu_type_t menu_type);
void menu_start(menu_ptr menu, int clear);
menu_ptr menu_goto(menu_ptr currentMenu, int depth, int element, int clear);
menu_ptr menu_add(menu_ptr parent, char * text, void (*function)());
void go_to_main_menu();
