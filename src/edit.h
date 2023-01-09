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

#define MENU_BUTTONS (\
kb_IsDown(kb_KeyYequ) || \
kb_IsDown(kb_KeyWindow) || \
kb_IsDown(kb_KeyZoom) || \
kb_IsDown(kb_KeyTrace) || \
kb_IsDown(kb_KeyGraph))

void edit_OpenEditor(struct context *studioContext);

#ifdef __cplusplus
}
#endif

#endif