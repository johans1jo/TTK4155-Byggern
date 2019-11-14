#include <stdio.h>
#include "oled.h"

// MAX_SUBMENUS angir hvor mye plass i minnet som skal settes av til undermeny-array
#define MAX_SUBMENUS 10

typedef enum {
	MAIN,
	IN_GAME
} menu_type_t;

// Menyelement
typedef struct Menu {
	char * text; // Teksten i menyelementet
	void (*function)(); // Funksjonen som skal kalles hvis det ikke finnes noen undermeny
	struct Menu * parent; // Pappameny :)
	struct Menu * subMenu[MAX_SUBMENUS]; // Undermeny. Array av pekere til menyelementer
} menu_t, *menu_ptr;

void menu_start_main();
menu_ptr menu_init(menu_type_t menu_type);
void menu_start(menu_ptr menu);
menu_ptr menu_goto(menu_ptr currentMenu, int depth, int element);
menu_ptr menu_add(menu_ptr parent, char * text, void (*function)());
