/**
 * --------------------------------------
 * 
 * eZ80 Studio Source Code - edit.h
 * By RoccoLox Programs and TIny_Hacker
 * Copyright 2022 - 2025
 * License: GPL-3.0
 * 
 * --------------------------------------
**/

#ifndef EDIT_H
#define EDIT_H

#include "defines.h"

#include <keypadc.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Redraw the editor view.
 * 
 * @param studioContext eZ80 Studio context struct.
 * @param studioPreferences eZ80 Studio preferences struct.
 */
void edit_RedrawEditor(struct context_t *studioContext, struct preferences_t *studioPreferences);

/**
 * @brief Opens the editor view.
 * 
 * @param studioContext eZ80 Studio context struct.
 * @param studioPreferences eZ80 Studio preferences struct.
 */
void edit_OpenEditor(struct context_t *studioContext, struct preferences_t *studioPreferences);

#ifdef __cplusplus
}
#endif

#endif