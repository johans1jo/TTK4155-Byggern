/**
 * @file
 * @brief The implementation of the menu-system.
 */

#include <stdio.h>
#include "oled.h"
#include "mode.h"

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
	//void (*function)(); // Funksjonen som skal kalles hvis det ikke finnes noen undermeny
	mode_t mode;
	int parameter;
	int submenu_count;
	struct Menu * parent; // Pappameny :)
	//struct Menu * subMenu[MAX_SUBMENUS]; // Undermeny. Array av pekere til menyelementer
	struct Menu * submenus; // Submeny array, address starting at submenus[0]
} menu_t, *menu_ptr;

/**
 * @brief Initializes the menu-system and chooses (sub)menu.
 *
 * @param The menu.
 */
menu_ptr menu_init(menu_type_t menu_type);

/**
 * @brief Adds a submenu.
 *
 * @param A menu-pointer to the menu.
 *
 * @param The submenu number.
 */
void menu_add_submenus(menu_ptr menu, int submenu_count);

/**
 * @brief Starts the menu-system.
 *
 * @param A menu-pointer to the menu.
 *
 * @param A boolean value determining if the display should be cleared or not.
 */
void menu_start(menu_ptr menu, int clear);

/**
 * @brief Goes to the desired (sub)menu.
 *
 * @param A menu-pointer to the current menu.
 *
 * @param The depth direction.
 *
 * @param The element.
 *
 * @param A boolean value determining if the display should be cleared or not.
 */
menu_ptr menu_goto(menu_ptr currentMenu, int depth, int element, int clear);

/**
 * @brief Sets the text, mode and parameter to the desired (sub)menu.
 *
 * @param A menu-pointer to the parent menu.
 *
 * @param The text to be set to the menu.
 *
 * @param The mode to be set to the menu.
 *
 * @param The parameter to be set to the menu.
 */
menu_ptr menu_add(menu_ptr parent, char * text, mode_t mode, int parameter);


void menu_free(menu_ptr menu);
