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

#include <graphx.h>
#include <stdint.h>
#include <fontlibc.h>

// Draw the main UI elements

void ui_DrawUIMain(uint8_t button) {
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
}

void ui_DrawMenuBox(unsigned int x, uint8_t y, uint8_t width, uint8_t height, uint8_t option) {
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
}

void ui_NoFile(void) {
    gfx_ZeroScreen();
    ui_DrawUIMain(0);
    fontlib_SetCursorPosition(81, 98);
    fontlib_DrawString("Open or create a file");
    fontlib_SetCursorPosition(103, 110);
    fontlib_DrawString("to get started.");
}
