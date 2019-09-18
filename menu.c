#include "menu.h"

// Initierer en meny

menu_t menu_init() {
	static menu_t menu = {
		"Hovedmeny",	// Menytekst
		NULL,					// Funksjon
		NULL,					// Parent
		{ NULL }			// Undermeny
	};

	static menu_t main1 = { "Main1", NULL, &menu, {NULL} };
	menu_add_sub(&menu, &main1);

	static menu_t main2 = { "Main2", &t0, &menu, {NULL} };
	menu_add_sub(&menu, &main2);

	static menu_t sub1 = { "Sub1", &t0u0, &main1, {NULL} };
	menu_add_sub(&main1, &sub1);

	static menu_t sub2 = { "Sub2", &t0u1, &main1, {NULL} };
	menu_add_sub(&main1, &sub2);

	return menu;
}

//Legg til en undermeny på et menyelement
void menu_add_sub(menu_ptr menu, menu_ptr subMenu) {
	int i = 0;
	while (menu->subMenu[i] != NULL) {
		i++;
	}
	menu->subMenu[i] = subMenu;
}

// Drar igang menyen og får den opp på skjermen
void menu_start(menu_ptr menu) {
	int depth = 0;
	int depthDirection = 0;
	int element = 0;
	menu_ptr currentMenu = menu;

	// Kjører inntil vi navigerer ut av menysystemet eller velger en funksjon
	while (depth != -1) {
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
			depth++;
			depthDirection = 1;
		} else if (input == LEFT) {
			depth--;
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
// Returnerer peker til man havner på etter å ha gått dit
// Returnerer NULL hvis menysystemet skal avsluttes
menu_ptr menu_goto(menu_ptr currentMenu, int depthDirection, int element) {
	// Fikser å gå til undermeny eller til overmeny
	if (depthDirection > 0) {
		currentMenu = currentMenu->subMenu[element];
		element = 0;
	} else if (depthDirection < 0) {
		currentMenu = currentMenu->parent;
	}

	// Hvis vi har kommet til et menyelement med en funksjon, så utføres funksjonen
	if (currentMenu->function != NULL) {
		currentMenu->function();
		return NULL;
	}

	// List opp alle elementene i menyen vi har kommet til
	oled_clear();
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
void t0() {
	printf("t0\r\n");
}
void t0u0() {
	printf("t0u0\r\n");
}
void t0u1() {
	printf("t0u1\r\n");
}
void t0u2() {
	printf("t0u2\r\n");
}
void t1() {
	printf("t1\r\n");
}
void t2u0() {
	printf("t2u0\r\n");
}
