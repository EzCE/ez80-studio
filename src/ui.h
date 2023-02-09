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

#include "utility.h"

#include <stdint.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

// Draw scrollbar
void ui_DrawScrollbar(unsigned int x, uint8_t y, uint8_t boxHeight, unsigned int totalLines, unsigned int startLine, uint8_t linesPerPage);

// Draw the main UI elements - the buttons and the scroll bar
void ui_DrawUIMain(uint8_t button, unsigned int totalLines, unsigned int startLine);

// Draw the menu boxes
void ui_DrawMenuBox(unsigned int x, uint8_t y, uint8_t width, uint8_t height, uint8_t option, unsigned int optionCount, ...);

// Do this when no file is opened
void ui_NoFile(void);

void ui_DrawCursor(uint8_t row, uint8_t column, bool cursorActive, bool erase);

void ui_UpdateAllText(struct context_t *studioContext, struct preferences_t *studioPreferences);

#ifdef __cplusplus
}
#endif

#endif
