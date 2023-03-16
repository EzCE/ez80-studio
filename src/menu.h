/**
 * --------------------------------------
 * 
 * ez80 Studio Source Code - menu.h
 * By RoccoLox Programs and TIny_Hacker
 * Copyright 2022 - 2023
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

// File options menu
void menu_File(struct context_t *studioContext, struct preferences_t *studioPreferences);

// Compile code
void menu_Compile(struct context_t *studioContext);

// Jump to specific line
void menu_Goto(struct context_t *studioContext);

// Special characters menu
void menu_Chars(struct context_t *studioContext);

// Settings/preferences
void menu_Settings(struct context_t *studioContext, struct preferences_t *studioPreferences);

#ifdef __cplusplus
}
#endif

#endif