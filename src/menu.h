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
void menu_File(struct context *studioContext);

// Compile code
void menu_Compile(struct context *studioContext);

// Special characters menu
void menu_Chars(void);

// Jump to labels
void menu_Labels(struct context *studioContext);

// Settings/preferences
void menu_Settings(struct context *studioPreferences);

#ifdef __cplusplus
}
#endif

#endif