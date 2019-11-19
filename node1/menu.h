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
	const char * text; // Pointer to menu text in PROGMEM
	mode_t mode;
	int parameter;
	int submenu_count;
	struct Menu * parent; // Parent menu element
	struct Menu * submenus; // Submenu array, address starting at submenus[0]
} menu_t, *menu_ptr;

/**
 * @brief Initializes the menu-system and chooses (sub)menu.
 *
 * @param[in] The menu.
 */
menu_ptr menu_init(menu_type_t menu_type);

/**
 * @brief Adds a submenu.
 *
 * @param[in] A menu-pointer to the menu.
 *
 * @param[in] The submenu number.
 */
void menu_add_submenus(menu_ptr menu, int submenu_count);

/**
 * @brief Starts the menu-system.
 *
 * @param[in] A menu-pointer to the menu.
 *
 * @param[in] A boolean value determining if the display should be cleared or not.
 */
void menu_start(menu_ptr menu, int clear);

/**
 * @brief Goes to the desired (sub)menu.
 *
 * @param[in] A menu-pointer to the current menu.
 *
 * @param[in] The depth direction.
 *
 * @param[in] The element.
 *
 * @param[in] A boolean value determining if the display should be cleared or not.
 */
menu_ptr menu_goto(menu_ptr currentMenu, int depth, int element, int clear);

/**
 * @brief Sets the text, mode and parameter to the desired (sub)menu.
 *
 * @param[in] A menu-pointer to the parent menu.
 *
 * @param[in] The text to be set to the menu.
 *
 * @param[in] The mode to be set to the menu.
 *
 * @param[in] The parameter to be set to the menu.
 */
menu_ptr menu_add(menu_ptr parent, const char * text, mode_t mode, int parameter);

/**
 * @brief Releases the menu.
 *
 * @param[in] A menu-pointer to the menu to be released.
 */
