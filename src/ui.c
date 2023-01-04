/**
 * --------------------------------------
 * 
 * ez80 Studio Source Code - ui.c
 * By RoccoLox Programs and TIny_Hacker
 * Copyright 2022 - 2023
 * License: GPL-3.0
 * 
 * --------------------------------------
**/

#include "defines.h"
#include "utility.h"

#include <graphx.h>
#include <stdint.h>
#include <stdarg.h>
#include <fontlibc.h>

// Draw scrollbar
void ui_DrawScrollbar(unsigned int totalLines, unsigned int startLine) {
    if (totalLines) {
        uint8_t scrollBarLength = 223 / (totalLines / 16);
        uint8_t scrollOffset = 223 / totalLines * startLine;

        gfx_SetColor(BACKGROUND);
        gfx_FillRectangle_NoClip(312, 0, 8, 223);
        gfx_SetColor(CURSOR);
        gfx_FillRectangle_NoClip(312, 0 + scrollOffset, 8, scrollBarLength);
    }
}

// Draw the main UI elements
void ui_DrawUIMain(uint8_t button, unsigned int totalLines, unsigned int startLine) {
    // Clear area behind buttons and scrollbar
    gfx_SetColor(BACKGROUND);
    gfx_FillRectangle_NoClip(0, 225, 385, 15);
    gfx_FillRectangle_NoClip(312, 0, 8, 223);

    // If a menu button is pressed, highlight it
    if (button) {
        gfx_SetColor(CURSOR);
        gfx_FillRectangle_NoClip(0 + (button - 1) * 65 - (button - 2), 225, 63, 15);
    }

    // Draw the borders around the buttons and scrollbar
    gfx_SetColor(OUTLINE);
    gfx_Rectangle_NoClip(0, 223, 320, 2);
    gfx_Rectangle_NoClip(310, 0, 2, 223);
    gfx_Rectangle_NoClip(63, 225, 2, 15);
    gfx_Rectangle_NoClip(127, 225, 2, 15);
    gfx_Rectangle_NoClip(191, 225, 2, 15);
    gfx_Rectangle_NoClip(255, 225, 2, 15);

    // Button text
    fontlib_SetCursorPosition(18, 227);
    fontlib_DrawString("File");
    fontlib_SetCursorPosition(71, 227);
    fontlib_DrawString("Compile");
    fontlib_SetCursorPosition(139, 227);
    fontlib_DrawString("Labels");
    fontlib_SetCursorPosition(206, 227);
    fontlib_DrawString("Chars");
    fontlib_SetCursorPosition(260, 227);
    fontlib_DrawString("Settings");

    ui_DrawScrollbar(totalLines, startLine);
}

// Draw a box with the menu items/cursor
void ui_DrawMenuBox(unsigned int x, uint8_t y, uint8_t width, uint8_t height, uint8_t option, unsigned int optionCount, ...) {
    gfx_SetColor(BACKGROUND);
    gfx_FillRectangle_NoClip(x, y, width, height);

    gfx_SetColor(OUTLINE);
    gfx_FillRectangle_NoClip(x + 1 + (2 * (x > 0)), y + 3 + (option * 17), width - 4 - (2 * ((x > 0) && (x + width < 310))), 17);

    // Menu outline
    gfx_FillRectangle_NoClip(x, y, width, 2);

    if (x > 0) {
        gfx_FillRectangle_NoClip(x, y + 2, 2, height - 2);
    }

    if (x + width < 310) {
        gfx_FillRectangle_NoClip(x + width - 2, y + 2, 2, height - 2);
    }

    va_list menuNames;
    va_start(menuNames, optionCount);

    fontlib_SetForegroundColor(TEXT_DEFAULT);

    for (unsigned int drawYOffset = 6; drawYOffset < 6 + optionCount * 17; drawYOffset += 17) {
        fontlib_SetCursorPosition(4, y + drawYOffset);
        fontlib_DrawString(va_arg(menuNames, char *));
    }

    va_end(menuNames);
}

// Do this when no file is open
void ui_NoFile(void) {
    gfx_ZeroScreen();
    ui_DrawUIMain(0, 0, 0);
    fontlib_SetCursorPosition(81, 98);
    fontlib_DrawString("Open or create a file");
    fontlib_SetCursorPosition(103, 110);
    fontlib_DrawString("to get started.");
}

// Print a line
void ui_PrintLine(char *, uint8_t row, unsigned int line) {
    //fontlib_SetCursorPosition(0, )
}
