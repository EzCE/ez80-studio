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

void edit_OpenEditor(struct context_t *studioContext, struct preferences_t *studioPreferences);

#ifdef __cplusplus
}
#endif

#endif