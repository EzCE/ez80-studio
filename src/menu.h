/**
 * --------------------------------------
 * 
 * eZ80 Studio Source Code - menu.h
 * By RoccoLox Programs and TIny_Hacker
 * Copyright 2022 - 2026
 * License: GPL-3.0
 * 
 * --------------------------------------
**/

#ifndef MENU_H
#define MENU_H

#include "defines.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Displays an error message based on the specified error code.
 * 
 * @param error Error message info to display.
 */
void menu_Error(struct error_t error);

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
 * @brief Displays a warning message based on the specified warning code.
 * 
 * @param warning Warning message code.
 * @return true Warning was acknowledged.
 * @return false Warning was ignored.
 */
bool menu_Warning(uint8_t warning);

/**
 * @brief Opens the file options menu.
 * 
 * @param studioContext eZ80 Studio context struct.
 * @param studioPreferences eZ80 Studio preferences struct.
 */
void menu_File(struct context_t *studioContext, struct preferences_t *studioPreferences);

/**
 * @brief Opens the line goto menu.
 * 
 * @param studioContext eZ80 Studio context struct.
 * @return The character selected, or '\0' if none were selected.
 */
void menu_Goto(struct context_t *studioContext);

/**
 * @brief Opens the special characters menu.
 * 
 * @param studioContext eZ80 Studio context struct.
 */
char menu_Chars(struct context_t *studioContext);

/**
 * @brief Opens the settings menu.
 * 
 * @param studioContext eZ80 Studio context struct.
 * @param studioPreferences eZ80 Studio preferences struct.
 */
void menu_Settings(struct context_t *studioContext, struct preferences_t *studioPreferences);

#ifdef __cplusplus
}
#endif

#endif