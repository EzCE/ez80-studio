/**
 * --------------------------------------
 * 
 * ez80 Studio Source Code - ui.h
 * By RoccoLox Programs and TIny_Hacker
 * Copyright 2022 - 2023
 * License: GPL-3.0
 * 
 * --------------------------------------
**/

#ifndef UI_H
#define UI_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Draw the main UI elements - the buttons and the scroll bar
void ui_DrawUIMain(uint8_t button);

// Draw the menu boxes
void ui_DrawMenuBox(unsigned int x, uint8_t y, uint8_t width, uint8_t height, uint8_t option);

// Do this when no file is opened
void ui_NoFile(void);

#ifdef __cplusplus
}
#endif

#endif
