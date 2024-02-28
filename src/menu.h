/**
 * --------------------------------------
 * 
 * ez80 Studio Source Code - menu.h
 * By RoccoLox Programs and TIny_Hacker
 * Copyright 2022 - 2024
 * License: GPL-3.0
 * 
 * --------------------------------------
**/

#ifndef MENU_H
#define MENU_H

#include "utility.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Check if a menu should be opened.
 * 
 * @param studioContext ez80 Studio context struct.
 * @param studioPreferences ez80 Studio preferences struct.
 */
void menu_CheckMenus(struct context_t *studioContext, struct preferences_t *studioPreferences);

/**
 * @brief Displays an error message based on the specified error code.
 * 
 * @param error Error code representing the error encountered.
 */
void menu_Error(uint8_t error);

/**
 * @brief Displays an option box for yes or no.
 * 
 * @param x X coordinate to begin drawing the box.
 * @param y Y coordinate to begin drawing the box.
 * @param buttonWidth Width of the yes and no buttons.
 * @return true The user selected yes.
 * @return false The user selected no.
 */
bool menu_YesNo(unsigned int x, uint8_t y, uint8_t buttonWidth);

/**
 * @brief Opens the file options menu.
 * 
 * @param studioContext ez80 Studio context struct.
 * @param studioPreferences ez80 Studio preferences struct.
 */
void menu_File(struct context_t *studioContext, struct preferences_t *studioPreferences);

/**
 * @brief Assembles the currently opened program.
 * 
 * @param studioContext ez80 Studio context struct.
 */
void menu_Assemble(struct context_t *studioContext);

/**
 * @brief Opens the line goto menu.
 * 
 * @param studioContext ez80 Studio context struct.
 * @return The character selected, or '\0' if none were selected.
 */
void menu_Goto(struct context_t *studioContext);

/**
 * @brief Opens the special characters menu.
 * 
 * @param studioContext ez80 Studio context struct.
 */
char menu_Chars(struct context_t *studioContext);

/**
 * @brief Opens the settings menu.
 * 
 * @param studioContext ez80 Studio context struct.
 * @param studioPreferences ez80 Studio preferences struct.
 */
void menu_Settings(struct context_t *studioContext, struct preferences_t *studioPreferences);

#ifdef __cplusplus
}
#endif

#endif