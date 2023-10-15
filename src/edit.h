/**
 * --------------------------------------
 * 
 * ez80 Studio Source Code - edit.h
 * By RoccoLox Programs and TIny_Hacker
 * Copyright 2022 - 2023
 * License: GPL-3.0
 * 
 * --------------------------------------
**/

#ifndef EDIT_H
#define EDIT_H

#include "utility.h"

#include <keypadc.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Opens the editor view.
 * 
 * @param studioContext ez80 Studio context struct.
 * @param studioPreferences ez80 Studio preferences struct.
 */
void edit_OpenEditor(struct context_t *studioContext, struct preferences_t *studioPreferences);

#ifdef __cplusplus
}
#endif

#endif