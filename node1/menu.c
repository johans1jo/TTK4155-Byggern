#include "menu.h"
#include "joystick.h"
#include <stdlib.h>
#include "draw.h"

// Initierer og lager en meny
menu_ptr menu_init() {
	// Initierer menyen
	menu_ptr menu = malloc(sizeof(menu_t));

	// Legger til menyelementer
	menu_ptr menu_highscore = menu_add(menu, "Highscore", &highscore);
	menu_ptr menu_play = menu_add(menu, "Play", NULL);
	menu_ptr menu_game1 = menu_add(menu_play, "Game1", &game1);
	menu_ptr menu_game2 = menu_add(menu_play, "Game2", &game2);
	menu_ptr menu_game3 = menu_add(menu_play, "Game3", &game3);
	menu_ptr menu_something = menu_add(menu, "Something", NULL);
	menu_ptr menu_something1 = menu_add(menu_something, "Something1", &something1);
	menu_ptr menu_something2 = menu_add(menu_something, "Something2", &something2);

	return menu;
}

// Legger et undermenyelement til "parent"-menyen.
// Hvis et menyelement har en "function", så blir funksjonen utført uansett om menyen har en undermeny
// Når man legger til et menyelement som skal ha en undermeny, så må "function" settes til NULL.
menu_ptr menu_add(menu_ptr parent, char * text, void (*function)()) {
	menu_ptr subMenu = malloc(sizeof(menu_t));
	subMenu->text = text;
	subMenu->function = function;
	subMenu->parent = parent;

	int i = 0;
	while (parent->subMenu[i] != NULL) {
		i++;
	}
	parent->subMenu[i] = subMenu;

	return subMenu;
}

// Drar igang menyen og får den opp på skjermen
void menu_start(menu_ptr menu) {
	int depthDirection = 0;
	int element = 0;
	menu_ptr currentMenu = menu;

	// Kjører inntil vi navigerer ut av menysystemet eller velger en funksjon
	while (!(depthDirection == -1 && currentMenu->parent == NULL)) {
		menu_ptr oldMenu = currentMenu;

		// Går til riktig meny basert på input eller standardverdier
		currentMenu = menu_goto(currentMenu, depthDirection, element);
		depthDirection = 0;

		// Går ut av menysystemet hvis vi har kommet til et menyelement med en funksjon
		if (currentMenu == NULL) {
			return;
		}

		// Sender brukeren til toppen av menyen hvis vi har kommet til en ny undermeny
		if (currentMenu != oldMenu) {
			element = 0;
		}

		// Henter input og går riktig vei i menyen
		while (joy_read_dir() != 0) {
		};
		while (joy_read_dir() == 0) {
		};
		int input = joy_read_dir();
		if (input == RIGHT) {
			depthDirection = 1;
		} else if (input == LEFT) {
			depthDirection = -1;
		} else if (input == UP) {
			// Passer på at vi ikke går over øverste menyelement
			if (element > 0) {
				element--;
			}
		} else if (input == DOWN) {
			// Passer på at vi ikke går under nederste menyelement
			if (currentMenu->subMenu[element+1] != NULL) {
				element++;
			}
		}
	}
}

// Gå til et menyelement, undermeny eller tilbake til "overmenyen"
// Returnerer peker til menyen man havner på etter å ha gått dit
// Returnerer NULL hvis menysystemet skal avsluttes
menu_ptr menu_goto(menu_ptr currentMenu, int depthDirection, int element) {
	// Fikser å gå til undermeny eller til overmeny
	if (depthDirection > 0) {
		currentMenu = currentMenu->subMenu[element];
		element = 0;
	} else if (depthDirection < 0) {
		currentMenu = currentMenu->parent;
	}

	// Rydder skjermen før vi utfører funksjonen eller printer en ny meny
	oled_clear();

	// Hvis vi har kommet til et menyelement med en funksjon, så utføres funksjonen
	if (currentMenu->function != NULL) {
		currentMenu->function();
		return NULL;
	}

	// List opp alle elementene i menyen vi har kommet til
	int i = 0;
	while (currentMenu->subMenu[i] != NULL) {
		oled_goto_line(i);
		oled_goto_column(0);
		if (i == element) {
			oled_print("-> ");
		}
		oled_print(currentMenu->subMenu[i]->text);
		i++;
	}

	// Returnerer peker til menyen vi har kommet til
	return currentMenu;
}

// Eksempelfunksjoner for testing
void highscore() {
	printf("Highscore\r\n");

	// Tegnegreier
	point points[] = {
		{0, 0},
		{10, 10},
		{50, 32}
	};
	draw_lines(points, sizeof(points)/sizeof(points[0]), 4);
	draw_print();

}
void game1() {
	printf("Game1\r\n");
	draw_point(20,20,7);
	draw_point(1,1,10);
	draw_print();
}
void game2() {
	printf("Game2\r\n");
}
void game3() {
	printf("Game3\r\n");
}
void something1() {
	printf("Something1\r\n");
}
void something2() {
	printf("Something2\r\n");
}
