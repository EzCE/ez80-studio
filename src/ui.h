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
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

// Draw the main UI elements - the buttons and the scroll bar
void ui_DrawUIMain(uint8_t button, unsigned int totalLines, unsigned int startLine);

// Draw scrollbar
void ui_DrawScrollbar(unsigned int totalLines, unsigned int startLine);

// Draw the menu boxes
void ui_DrawMenuBox(unsigned int x, uint8_t y, uint8_t width, uint8_t height, uint8_t option, unsigned int optionCount, ...);

// Do this when no file is opened
void ui_NoFile(void);

char *ui_PrintLine(char *string, uint8_t *row, unsigned int line, bool updateRow);

void ui_UpdateAllText(char *textStart, unsigned int lineStart, unsigned int totalNewlines);

#ifdef __cplusplus
}
#endif

#endif
