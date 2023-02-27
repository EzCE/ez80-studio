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
#include "highlight.h"

#include <graphx.h>
#include <stdint.h>
#include <stdarg.h>
#include <fontlibc.h>

// Draw scrollbar
void ui_DrawScrollbar(unsigned int x, uint8_t y, uint8_t boxHeight, unsigned int totalLines, unsigned int startLine, uint8_t linesPerPage) {
    if (totalLines) {
        unsigned int scrollBarLength = (float)boxHeight / ((float)totalLines / (float)linesPerPage) + 1;
        
        if (scrollBarLength > boxHeight) {
            scrollBarLength = boxHeight;
        }

        uint8_t scrollOffset = (float)boxHeight / (float)totalLines * (float)startLine;

        gfx_SetColor(BACKGROUND);
        gfx_FillRectangle_NoClip(x, y, 8, boxHeight);
        gfx_SetColor(CURSOR);
        gfx_FillRectangle_NoClip(x, y + scrollOffset, 8, scrollBarLength);
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
    fontlib_SetForegroundColor(TEXT_DEFAULT);
    fontlib_SetCursorPosition(18, 227);
    fontlib_DrawString("File");
    fontlib_SetCursorPosition(71, 227);
    fontlib_DrawString("Compile");
    fontlib_SetCursorPosition(130, 227);
    fontlib_DrawString("Goto");
    fontlib_ShiftCursorPosition(4, 0); // Do this because a space won't fit
    fontlib_DrawString("Line");
    fontlib_SetCursorPosition(206, 227);
    fontlib_DrawString("Chars");
    fontlib_SetCursorPosition(260, 227);
    fontlib_DrawString("Settings");

    ui_DrawScrollbar(312, 0, 223, totalLines, startLine, 14);
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

    if (y + height < 223) {
        gfx_FillRectangle_NoClip(x, y + height - 2, width, 2);
    }

    va_list menuNames;
    va_start(menuNames, optionCount);

    fontlib_SetForegroundColor(TEXT_DEFAULT);

    for (unsigned int drawYOffset = 6; drawYOffset < 6 + optionCount * 17; drawYOffset += 17) {
        fontlib_SetCursorPosition(x + 4 + (2 * (x > 0)), y + drawYOffset);
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

// Check if top line was a highlightComment, string, etc.
static bool ui_CheckIsComment(char *dataStart, char *fileStart) {
    while (dataStart >= fileStart && *dataStart != '\n') {
        if (*dataStart == ';') {
            return true; // No need to keep searching
        }

        dataStart--;
    }

    return false;
}

static bool ui_CheckIsString(char *dataStart, char *fileStart) {
    uint8_t isString = '\0';

    while (dataStart >= fileStart && *dataStart != '\n') {
        if (*dataStart == '\"' || *dataStart == '\'') {
            if (*dataStart == isString && *(dataStart - 1) != '\\') { // Close string
                isString = '\0';
            } else { // Open string
                isString = *dataStart;
            }
        }

        dataStart--;
    }

    return isString;
}

// Print a line
static char *ui_PrintLine(char *string, char *fileDataStart, char *openEOF, bool highlighting, uint8_t *row, unsigned int line, unsigned int pageStart, bool updateRow) {
    uint8_t currentRow = *row; // We might not want to update *row
    char *stringEnd = util_GetStringEnd(string, openEOF);

    fontlib_SetCursorPosition(0, 2 + currentRow * 16);

    if ((*(string - 1) == '\n') || !(pageStart)) {
        fontlib_SetForegroundColor(TEXT_DEFAULT);
        fontlib_DrawInt(line, 4);
        fontlib_DrawString(": ");
    } else {
        fontlib_ShiftCursorPosition(42, 0);
    }

    bool highlightComment = false;
    uint8_t highlightString = '\0';

    if (!(*row)) { // Ensure wrapped comments are properly highlighted
        if (highlighting && ui_CheckIsComment(string, fileDataStart)) {
            fontlib_SetForegroundColor(TEXT_COMMENT);
            highlightComment = true;
        } else if (highlighting && ui_CheckIsString(string, fileDataStart)) {
            fontlib_SetForegroundColor(TEXT_STRING);
            highlightString = true;
        } else {
            fontlib_SetForegroundColor(hlight_GetHighlightColor(string, stringEnd, highlighting));
        }
    } else {
        fontlib_SetForegroundColor(hlight_GetHighlightColor(string, stringEnd, highlighting));
    }

    uint8_t charsDrawn = 0;

    while (*string != '\n' && string != openEOF + 1) {
        if (!highlightString && highlighting && *string == ';') {
            fontlib_SetForegroundColor(TEXT_COMMENT);
            highlightComment = true;
        } else if (!highlightComment && highlighting && (*string == '\"' || *string == '\'')) {
            if (highlightString == *string && *(string - 1) != '\\') {
                fontlib_SetForegroundColor(TEXT_STRING);
                highlightString = '\0';
            } else {
                fontlib_SetForegroundColor(TEXT_STRING);
                highlightString = *string;
            }
        } else if (string >= stringEnd && !highlightComment && !highlightString) {
            stringEnd = util_GetStringEnd(string, openEOF);
            fontlib_SetForegroundColor(hlight_GetHighlightColor(string, stringEnd, highlighting));
        }

        fontlib_DrawGlyph(*string);

        charsDrawn++;
        string++;

        if (charsDrawn == 38 && *string != '\n') { // Loop to next line if the text continues past the edge
            charsDrawn = 0;
            currentRow++;

            if (updateRow) {
                *row = *row + 1;
            }

            if (currentRow < 14) {
                fontlib_SetCursorPosition(42, 2 + currentRow * 16);
            } else {
                return string; // We can't draw anymore on the screen, so return early
            }
        }
    }

    string++; // Skip newline
    return string;
}

void ui_DrawCursor(uint8_t row, uint8_t column, bool cursorActive, bool erase) {
    if (erase) {
        gfx_SetColor(BACKGROUND);
    } else {
        gfx_SetColor(CURSOR);
    }

    gfx_FillRectangle_NoClip(0, 1 + row * 16, 310, 1); // Highlight currently selected row
    gfx_FillRectangle_NoClip(0, 14 + row * 16, 310, 1);

    if (!cursorActive) {
        gfx_SetColor(BACKGROUND);
    }

    gfx_FillRectangle_NoClip(41 + column * 7, 3 + row * 16, 2, 10); // Cursor
}

void ui_UpdateAllText(struct context_t *studioContext, struct preferences_t *studioPreferences) {
    gfx_SetColor(BACKGROUND);
    gfx_FillRectangle_NoClip(0, 0, 310, 223);

    unsigned int currentLine = studioContext->newlineStart + 1;
    char *textStart = studioContext->pageDataStart;

    for (uint8_t row = 0; row < 14; row++) {
        textStart = ui_PrintLine(textStart, studioContext->fileDataStart, studioContext->openEOF, studioPreferences->highlighting, &row, currentLine, studioContext->lineStart, true);
        currentLine++;

        if (currentLine > studioContext->newlineCount) {
            break;
        }
    }
}
