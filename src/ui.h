/**
 * --------------------------------------
 * 
 * eZ80 Studio Source Code - ui.h
 * By RoccoLox Programs and TIny_Hacker
 * Copyright 2022 - 2024
 * License: GPL-3.0
 * 
 * --------------------------------------
**/

#ifndef UI_H
#define UI_H

#include "defines.h"

#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Draws a scrollbar
 * 
 * @param x X coordinate to begin drawing the scrollbar at.
 * @param y Y coordinate to begin drawing the scrollbar at.
 * @param boxHeight Total height of the scrollbar box.
 * @param totalLines Number of total lines that the scrollbar represents.
 * @param startLine Line at which the scrollbar starts.
 * @param linesPerPage Number of lines per page.
 */
void ui_DrawScrollbar(unsigned int x, uint8_t y, uint8_t boxHeight, unsigned int totalLines, unsigned int startLine, uint8_t linesPerPage);

/**
 * @brief Draws the main UI elements.
 * 
 * @param button 1 - 5 for a button to be highlighted, or 0 if no buttons are highlighted.
 * @param totalLines Total number of lines in the current file.
 * @param startLine Line at the top of the current page.
 */
void ui_DrawUIMain(uint8_t button, unsigned int totalLines, unsigned int startLine);

/**
 * @brief Draws a menu box.
 * 
 * @param x X coordinate to start drawing the menu box at.
 * @param y Y coordinate to begin drawing the menu box at.
 * @param width Width of the menu box.
 * @param height Height of the menu box.
 * @param option Currently selected option.
 * @param optionCount Total number of options in the menu.
 * @param ... Option names, in order from top to bottom.
 */
void ui_DrawMenuBox(unsigned int x, uint8_t y, uint8_t width, uint8_t height, uint8_t option, unsigned int optionCount, ...);

/**
 * @brief Main screen when no file is currently opened.
 * 
 */
void ui_NoFile(void);

/**
 * @brief Draws the cursor and highlights the currently selected row.
 * 
 * @param row Currently selected row.
 * @param column Currently selected column.
 * @param cursorActive Whether or not the cursor is active (used for blinking animation).
 * @param erase If true, erase the footprint of the cursor and line highlight.
 */
void ui_DrawCursor(uint8_t row, uint8_t column, bool cursorActive, bool erase);

/**
 * @brief Update all text currently drawn on the screen.
 * 
 * @param studioContext eZ80 Studio context struct.
 * @param studioPreferences eZ80 Studio preferences struct.
 */
void ui_UpdateAllText(struct context_t *studioContext, struct preferences_t *studioPreferences);

#ifdef __cplusplus
}
#endif

#endif
