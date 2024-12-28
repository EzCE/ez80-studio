/**
 * --------------------------------------
 * 
 * eZ80 Studio Source Code - ui.c
 * By RoccoLox Programs and TIny_Hacker
 * Copyright 2022 - 2024
 * License: GPL-3.0
 * 
 * --------------------------------------
**/

#include "defines.h"
#include "utility.h"
#include "highlight.h"
#include "asm/files.h"
#include "asm/spi.h"

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
    gfx_FillRectangle_NoClip(0, 225, 320, 15);
    gfx_FillRectangle_NoClip(312, 14, 8, 209);

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
    fontlib_SetCursorPosition(78, 227);
    fontlib_DrawString("Build");
    fontlib_SetCursorPosition(146, 227);
    fontlib_DrawString("Goto");
    fontlib_SetCursorPosition(206, 227);
    fontlib_DrawString("Chars");
    fontlib_SetCursorPosition(260, 227);
    fontlib_DrawString("Settings");

    ui_DrawScrollbar(312, 14, 209, totalLines, startLine, 14);
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
static bool ui_CheckIsComment(char *dataStart) {
    while (dataStart >= (char *)EDIT_BUFFER && *dataStart != '\n') {
        if (*dataStart == ';') {
            return true; // No need to keep searching
        }

        dataStart--;
    }

    return false;
}

static bool ui_CheckIsString(char *dataStart) {
    bool isString = false;

    if ((*dataStart == '\"' || *dataStart == '\'') && (*(dataStart - 1) != '\\')) {
        return true;
    }

    while (dataStart >= (char *)EDIT_BUFFER && *dataStart != '\n') {
        if ((*dataStart == '\"' || *dataStart == '\'') && (*(dataStart - 1) != '\\')) {
            isString = !isString;
        }

        dataStart--;
    }

    return isString;
}

// Print a line
static char *ui_PrintLine(struct context_t *studioContext, char *string, bool highlighting, uint8_t row, unsigned int line) {
    bool highlightComment = false;
    bool highlightString = false;
    bool highlightInstruction = false;
    char *stringEnd = util_GetStringEnd(string, studioContext->openEOF, false);

    fontlib_SetCursorPosition(0, 2 + row * 16);

    if ((*(string - 1) == '\n') || (!(studioContext->lineStart) && !row)) {
        fontlib_SetForegroundColor(TEXT_DEFAULT);
        fontlib_DrawInt(line, 4);
        fontlib_DrawString(": ");
    } else {
        fontlib_ShiftCursorPosition(42, 0);
    }

    if (highlighting) { // correctly highlight first item in case it was wrapped from a previous line
        char *tempString = util_GetStringStart(string);

        if (ui_CheckIsComment(tempString)) {
            fontlib_SetForegroundColor(TEXT_COMMENT);
            highlightComment = true;
        } else if (ui_CheckIsString(tempString)) {
            fontlib_SetForegroundColor(TEXT_STRING);
            highlightString = true;
        } else {
            fontlib_SetForegroundColor(hlight_GetHighlightColor(tempString, stringEnd, highlighting));
        }
    }

    uint8_t charsDrawn = 0;

    while (*string != '\n' && string <= studioContext->openEOF) {
        if (string >= stringEnd && highlighting) {
            if (fontlib_GetForegroundColor() == TEXT_INSTRUCTION) {
                highlightInstruction = true;
            }

            if (!highlightString && *string == ';') {
                fontlib_SetForegroundColor(TEXT_COMMENT);
                highlightComment = true;
            }

            if (!highlightComment) {
                if (*string == '\"' || *string == '\'' || *(string - 1) == '\"' || *(string - 1) == '\'') {
                    if (ui_CheckIsString(string)) {
                        fontlib_SetForegroundColor(TEXT_STRING);
                        highlightString = true;
                    } else if (highlightString) {
                        stringEnd = util_GetStringEnd(string, studioContext->openEOF, false);
                        fontlib_SetForegroundColor(hlight_GetHighlightColor(string, stringEnd, highlighting));
                        highlightString = false;
                    }
                }
            }

            if (!highlightComment && !highlightString) {
                stringEnd = util_GetStringEnd(string, studioContext->openEOF, false);
                fontlib_SetForegroundColor(hlight_GetHighlightColor(string, stringEnd, highlighting));
            }

            if (fontlib_GetForegroundColor() == TEXT_DEFAULT && highlightInstruction && ((unsigned)(*string - '0') < 10 || (unsigned)(*string - 'A') < 26 || (unsigned)(*string - 'a') < 26 || *string == '.' || *string == '_')) {
                fontlib_SetForegroundColor(TEXT_LABEL);
            }

        }

        fontlib_DrawGlyph(*string);

        charsDrawn++;
        string++;

        if (charsDrawn == 38 && *string != '\n') { // Loop to next line if the text continues past the edge
            return string;
        }
    }

    string++; // Skip newline
    return string;
}

void ui_DrawCursor(uint8_t row, uint8_t column, bool cursorActive, bool erase) {
    asm_spi_BeginFrame();

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

void ui_UpdateText(struct context_t *studioContext, struct preferences_t *studioPreferences, uint8_t drawMode) {
    bool highlighting = studioPreferences->highlighting;
    gfx_SetColor(BACKGROUND);

    switch (drawMode) {
        case UPDATE_ALL:
            gfx_FillRectangle_NoClip(0, 0, 310, 223);
            break;
        case UPDATE_TOP:
            gfx_FillRectangle_NoClip(0, 1, 310, 14);
            break;
        case UPDATE_BOTTOM:
            gfx_FillRectangle_NoClip(0, 209, 310, 14);
            break;
        default:
            break;
    }

    unsigned int currentLine = studioContext->newlineStart + 1;
    char *textStart = studioContext->pageDataStart;

    for (uint8_t row = 0; row < 14; row++) {
        if (row == 13 || drawMode != UPDATE_BOTTOM) {
            textStart = ui_PrintLine(studioContext, textStart, highlighting, row, currentLine);
        } else {
            textStart = asm_files_NextLine(textStart);
        }

        if (drawMode == UPDATE_TOP) {
            return;
        }

        currentLine += (*(textStart - 1) == '\n');

        if (textStart > studioContext->openEOF + 1) {
            break;
        }
    }
}
