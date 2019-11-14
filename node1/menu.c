#include "menu.h"
#include "joystick.h"
#include <stdlib.h>
#include "draw.h"
#include "can.h"
#include "highscore.h"
#include "game.h"
#define F_CPU 4915200
#include <util/delay.h>
#include "buttons.h"

// Initierer og lager en meny
menu_ptr menu_init(menu_type_t menu_type) {
	// Initierer menyen
	menu_ptr menu = malloc(sizeof(menu_t));
	printf("malloc %d\r\n", menu);

	if (menu_type == MAIN) {
		// Legger til menyelementer
		menu_add(menu, "Spill :)", &game_play);
		menu_ptr menu_settings = menu_add(menu, "Innstillinger", NULL);
			menu_ptr menu_difficulty = menu_add(menu_settings, "Vanskegrad", NULL);
				menu_add(menu_difficulty, "Vanskelig", &game_set_difficulty_hard);
				menu_add(menu_difficulty, "Middels", &game_set_difficulty_medium);
				menu_add(menu_difficulty, "Lett", &game_set_difficulty_easy);
			menu_ptr menu_users = menu_add(menu_settings, "Velg bruker", NULL);
				menu_add(menu_users, "Lag ny bruker", NULL);
				// Mulig å velge eksisterende bruker
		menu_add(menu, "Highscore", &highscore_show);

	} else if (menu_type == IN_GAME) {
		menu_add(menu, "Avslutt :o", &game_stop);
		menu_add(menu, "Pause :/", &game_pause);

	} else if (menu_type == HIGHSCORE) {
		menu_add(menu, "Til hovedmeny", &go_to_main_menu);
	}

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
void menu_start(menu_ptr menu, int clear) {
	int depthDirection = 0;
	int element = 0;
	menu_ptr currentMenu = menu;

	// Kjører inntil vi navigerer ut av menysystemet eller velger en funksjon
	while (!(depthDirection == -1 && currentMenu->parent == NULL)) {
		menu_ptr oldMenu = currentMenu;

		// Går til riktig meny basert på input eller standardverdier
		currentMenu = menu_goto(currentMenu, depthDirection, element, clear);
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
		//printf("condition: %d\r\n", game_is_on() == (buttons_right() > 0));
		while (joy_read_dir() != 0 || !(game_is_on() == (buttons_right() > 0))) {
			_delay_ms(10);
		};
		while (joy_read_dir() == 0 || !(game_is_on() == (buttons_right() > 0))) {
			_delay_ms(10);
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
menu_ptr menu_goto(menu_ptr currentMenu, int depthDirection, int element, int clear) {
	// Fikser å gå til undermeny eller til overmeny
	if (depthDirection > 0) {
		currentMenu = currentMenu->subMenu[element];
		element = 0;
	} else if (depthDirection < 0) {
		currentMenu = currentMenu->parent;
	}

	// Rydder skjermen før vi utfører funksjonen eller printer en ny meny
	if (clear) {
		oled_clear();
	}

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

void go_to_main_menu() {
	// Do nothing aka go back to main menu in the main while :)
}
