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
#include "game.h"
#include <avr/pgmspace.h>
#include "fonts.h"

// Initialize menu text strings in progmem
const char text_main_menu[] PROGMEM = "Main menu";
const char text_play[] PROGMEM = "Play :)";
const char text_settings[] PROGMEM = "Settings";
const char text_highscores[] PROGMEM = "Highscores";
const char text_choose_user[] PROGMEM = "Choose user";
const char text_edit_users[] PROGMEM = "Edit users";
const char text_difficulty[] PROGMEM = "Difficulty";
const char text_hard[] PROGMEM = "Hard";
const char text_medium[] PROGMEM = "Medium";
const char text_easy[] PROGMEM = "Easy";
const char text_in_game[] PROGMEM = "In-game";
const char text_quit[] PROGMEM = "Quit";

// String array in progmem maybe?

// Initierer og lager en meny
menu_ptr menu_init(menu_type_t menu_type) {
	// Initierer menyen
	menu_ptr menu = malloc(sizeof(menu_t));
	menu->submenu_count = 0;
	menu->mode = NO_MODE;
	printf("malloc %d\r\n", menu);

	if (menu_type == MAIN) {
		menu->text = text_main_menu;
		menu_add_submenus(menu, 3);
		menu_add(menu, text_play, PLAY_GAME, 0);
		menu_ptr menu_settings = menu_add(menu, text_settings, 0, 0);
		menu_add(menu, text_highscores, SHOW_HIGHSCORE, 0);

		menu_add_submenus(menu_settings, 3);
		menu_ptr menu_choose_users = menu_add(menu_settings, text_choose_user, 0, 0);
		menu_ptr menu_edit_users = menu_add(menu_settings, text_edit_users, 0, 0);
		menu_ptr menu_difficulty = menu_add(menu_settings, text_difficulty, 0, 0);

		menu_add_submenus(menu_edit_users, 5);
		menu_add(menu_edit_users, game_get_user_name(0), EDIT_USER, 0);
		menu_add(menu_edit_users, game_get_user_name(1), EDIT_USER, 1);
		menu_add(menu_edit_users, game_get_user_name(2), EDIT_USER, 2);
		menu_add(menu_edit_users, game_get_user_name(3), EDIT_USER, 3);
		menu_add(menu_edit_users, game_get_user_name(4), EDIT_USER, 4);

		menu_add_submenus(menu_choose_users, 5);
		menu_add(menu_choose_users, game_get_user_name(0), CHOOSE_USER, 0);
		menu_add(menu_choose_users, game_get_user_name(1), CHOOSE_USER, 1);
		menu_add(menu_choose_users, game_get_user_name(2), CHOOSE_USER, 2);
		menu_add(menu_choose_users, game_get_user_name(3), CHOOSE_USER, 3);
		menu_add(menu_choose_users, game_get_user_name(4), CHOOSE_USER, 4);

		menu_add_submenus(menu_difficulty, 3);
		menu_add(menu_difficulty, text_hard, CHOOSE_DIFFICULTY, 3);
		menu_add(menu_difficulty, text_medium, CHOOSE_DIFFICULTY, 2);
		menu_add(menu_difficulty, text_easy, CHOOSE_DIFFICULTY, 1);

	} else if (menu_type == IN_GAME) {
		menu->text = text_in_game;
		menu_add_submenus(menu, 1);
		menu_add(menu, text_quit, PLAY_GAME, 1);

	} else if (menu_type == HIGHSCORE) {
		menu->text = text_highscores;
		menu_add_submenus(menu, 1);
		menu_add(menu, text_quit, MAIN_MENU, 0);
	}
	return menu;
}

void menu_add_submenus(menu_ptr menu, int submenu_count) {
	menu_ptr submenus = malloc(sizeof(menu_t)*submenu_count);
	printf("malloc (%d) %d\r\n", submenu_count, submenus);
	menu->submenus = submenus;
}

// Legger et undermenyelement til "parent"-menyen.
// Hvis et menyelement har en "function", så blir funksjonen utført uansett om menyen har en undermeny
// Når man legger til et menyelement som skal ha en undermeny, så må "function" settes til NULL.
menu_ptr menu_add(menu_ptr parent, const char * text, mode_t mode, int parameter) {
	menu_t subMenu;
	subMenu.text = text;
	subMenu.mode = mode;
	subMenu.parameter = parameter;
	subMenu.parent = parent;
	subMenu.submenu_count = 0;

	parent->submenus[parent->submenu_count] = subMenu;
	parent->submenu_count += 1;

	return &(parent->submenus[parent->submenu_count - 1]);
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
			printf("return null\r\n");
			return;
		}

		// Sender brukeren til toppen av menyen hvis vi har kommet til en ny undermeny
		if (currentMenu != oldMenu) {
			element = 0;
		}

		// Henter input og går riktig vei i menyen
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
			if (element + 1 < currentMenu->submenu_count) {
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
		currentMenu = &currentMenu->submenus[element];
		element = 0;
	} else if (depthDirection < 0) {
		currentMenu = currentMenu->parent;
	}

	// Rydder skjermen før vi utfører funksjonen eller printer en ny meny
	if (clear) {
		oled_clear();
	}

	// Hvis vi har kommet til et menyelement med en funksjon, så utføres funksjonen
	if (currentMenu->mode != NO_MODE) {
		mode_set(currentMenu->mode, currentMenu->parameter);
		return NULL;
	}

	// List opp alle elementene i menyen vi har kommet til
	int i = 0;
	oled_goto_line(0);
	oled_goto_column(0);
	oled_print_pgm(currentMenu->text);
	while (i < currentMenu->submenu_count) {
		oled_goto_line(1+i);
		oled_goto_column(0);
		if (i == element) {
			oled_print("-> ");
		} else {
			oled_print("   ");
		}
		//oled_print(currentMenu->subMenu[i]->text);
		if (currentMenu->text == text_edit_users || currentMenu->text == text_choose_user) {
			oled_print(currentMenu->submenus[i].text);
		} else {
			oled_print_pgm(currentMenu->submenus[i].text);
		}
		i++;
	}

	// Returnerer peker til menyen vi har kommet til
	return currentMenu;
}
