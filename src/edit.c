/**
 * --------------------------------------
 * 
 * ez80 Studio Source Code - utility.c
 * By RoccoLox Programs and TIny_Hacker
 * Copyright 2022 - 2024
 * License: GPL-3.0
 * 
 * --------------------------------------
**/

#include "edit.h"
#include "utility.h"
#include "ui.h"
#include "menu.h"
#include "defines.h"
#include "asm/files.h"
#include "asm/spi.h"

#include <graphx.h>
#include <keypadc.h>
#include <fontlibc.h>
#include <time.h>

void edit_RedrawEditor(struct context_t *studioContext, struct preferences_t *studioPreferences) {
    spi_beginFrame();
    gfx_ZeroScreen();

    if (studioContext->fileIsOpen) {
        ui_DrawUIMain(0, studioContext->totalLines, studioContext->lineStart);
        ui_UpdateAllText(studioContext, studioPreferences);
        ui_DrawCursor(studioContext->row, studioContext->column, true, false);
    } else {
        ui_NoFile();
    }

    spi_endFrame();
}

static bool edit_CursorUp(struct context_t *studioContext) {
    if (studioContext->row) {
        studioContext->row--;
        studioContext->rowDataStart = files_PreviousLine(studioContext->rowDataStart, studioContext->fileDataStart, studioContext->openEOF);
        studioContext->rowLength = files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
    } else if (studioContext->lineStart) {
        studioContext->newlineStart -= ((*(studioContext->pageDataStart - 1) == '\n') || !(studioContext->lineStart));
        studioContext->lineStart--;
        studioContext->pageDataStart = files_PreviousLine(studioContext->pageDataStart, studioContext->fileDataStart, studioContext->openEOF);
        studioContext->rowDataStart = studioContext->pageDataStart;
        studioContext->rowLength = files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
        return true;
    } else {
        studioContext->column = 0;
    }

    return false;
}

static bool edit_CursorDown(struct context_t *studioContext) {
    if (studioContext->row < 13 && studioContext->lineStart + studioContext->row + 1 != studioContext->totalLines) {
        studioContext->row++;
        studioContext->rowDataStart = files_NextLine(studioContext->rowDataStart);
        studioContext->rowLength = files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
    } else if (studioContext->lineStart + 14 < studioContext->totalLines) {
        studioContext->lineStart++;
        studioContext->pageDataStart = files_NextLine(studioContext->pageDataStart);
        studioContext->rowDataStart = files_NextLine(studioContext->rowDataStart);
        studioContext->rowLength = files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
        studioContext->newlineStart += (*(studioContext->pageDataStart - 1) == '\n');
        return true;
    } else {
        studioContext->column = studioContext->rowLength;
    }

    return false;
}

static bool edit_CursorLeft(struct context_t *studioContext) {
    if (studioContext->column) {
        studioContext->column--;
    } else {
        if (studioContext->row) {
            studioContext->row--;
            studioContext->rowDataStart = files_PreviousLine(studioContext->rowDataStart, studioContext->fileDataStart, studioContext->openEOF);
            studioContext->rowLength = files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
            studioContext->column = studioContext->rowLength;
        } else if (studioContext->lineStart) {
            studioContext->lineStart--;
            studioContext->pageDataStart = files_PreviousLine(studioContext->pageDataStart, studioContext->fileDataStart, studioContext->openEOF);
            studioContext->rowDataStart = studioContext->pageDataStart;
            studioContext->rowLength = files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
            studioContext->column = studioContext->rowLength;
            studioContext->newlineStart -= ((*(studioContext->pageDataStart - 1) == '\n') || !(studioContext->lineStart));
            return true;
        }
    }

    return false;
}

static bool edit_CursorRight(struct context_t *studioContext) {
    if (studioContext->column < studioContext->rowLength) {
        studioContext->column++;
    } else {
        if (studioContext->row < 13 && studioContext->lineStart + studioContext->row + 1 != studioContext->totalLines) {
            studioContext->row++;
            studioContext->rowDataStart = files_NextLine(studioContext->rowDataStart);
            studioContext->rowLength = files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
            studioContext->column = 0;
        } else if (studioContext->lineStart + 14 < studioContext->totalLines) {
            studioContext->lineStart++;
            studioContext->pageDataStart = files_NextLine(studioContext->pageDataStart);
            studioContext->rowDataStart = files_NextLine(studioContext->rowDataStart);
            studioContext->rowLength = files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
            studioContext->column = 0;
            studioContext->newlineStart += (*(studioContext->pageDataStart - 1) == '\n');
            return true;
        }
    }

    return false;
}

static void edit_Delete(struct context_t *studioContext) {
    if (studioContext->fileIsSaved) {
        studioContext->fileIsSaved = false;
    }

    files_DeleteChar(studioContext->rowDataStart + studioContext->column, studioContext->openEOF - (studioContext->rowDataStart + studioContext->column - 1));
    studioContext->openEOF--;
    studioContext->fileSize--;

    files_CountLines(studioContext->fileDataStart, &(studioContext->newlineCount), &(studioContext->totalLines), studioContext->openEOF);

    if (studioContext->lineStart && studioContext->lineStart + 12 >= studioContext->totalLines - 1) {
        studioContext->row++;
        studioContext->lineStart--;
        studioContext->pageDataStart = files_PreviousLine(studioContext->pageDataStart, studioContext->fileDataStart, studioContext->openEOF);
        studioContext->newlineStart -= ((*(studioContext->pageDataStart - 1) == '\n') || !(studioContext->lineStart));
    }

    if (!studioContext->column && *(studioContext->rowDataStart) == '\n' && *(studioContext->rowDataStart) - 1 != '\n' && studioContext->rowDataStart != studioContext->fileDataStart) {
        studioContext->rowDataStart = files_PreviousLine(studioContext->rowDataStart + 1, studioContext->fileDataStart, studioContext->openEOF);

        if (studioContext->row) {
            studioContext->row--;
        } else {
            studioContext->lineStart--;
            studioContext->pageDataStart = studioContext->rowDataStart;
        }

        studioContext->column = studioContext->rowLength;
    }

    studioContext->rowLength = files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
}

void edit_OpenEditor(struct context_t *studioContext, struct preferences_t *studioPreferences) {
    while (kb_AnyKey());

    bool keyPressed = false;
    bool cursorActive = true;
    bool redraw = false;

    uint8_t key = 0;
    uint8_t inputMode = INPUT_LOWERCASE;
    uint8_t inputChar = '\0';

    studioContext->fileIsSaved = true;

    spi_beginFrame();
    edit_RedrawEditor(studioContext, studioPreferences);
    spi_endFrame();

    clock_t clockOffset = clock(); // Keep track of an offset for timer stuff

    while (studioContext->fileIsOpen) {
        kb_Scan();

        if (!kb_AnyKey() && keyPressed) {
            keyPressed = false;
            clockOffset = clock();
        }

        if (kb_AnyKey() && (!keyPressed || clock() - clockOffset > CLOCKS_PER_SEC / 32)) {
            cursorActive = true;

            spi_beginFrame();
            ui_DrawCursor(studioContext->row, studioContext->column, cursorActive, true); // Erase old cursor

            if (kb_IsDown(kb_KeyClear)) {
                if (!studioContext->fileIsSaved) {
                    spi_beginFrame();
                    gfx_SetColor(OUTLINE);
                    gfx_FillRectangle_NoClip(80, 68, 150, 87);
                    gfx_SetColor(BACKGROUND);
                    gfx_FillRectangle_NoClip(82, 84, 146, 69);
                    fontlib_SetForegroundColor(TEXT_DEFAULT);
                    fontlib_SetCursorPosition(130, 70);
                    fontlib_DrawString("Warning");
                    fontlib_SetCursorPosition(85, 85);
                    fontlib_DrawString("The currently opened");
                    fontlib_SetCursorPosition(85, 96);
                    fontlib_DrawString("file has unsaved");
                    fontlib_SetCursorPosition(85, 108);
                    fontlib_DrawString("changes. Do you wish");
                    fontlib_SetCursorPosition(85, 121);
                    fontlib_DrawString("to discard them?");
                    spi_endFrame();

                    if (menu_YesNo(83, 136, 71)) {
                        studioContext->fileIsOpen = false;
                    } else {
                        redraw = true;
                        edit_RedrawEditor(studioContext, studioPreferences);
                        while (kb_AnyKey());
                    }
                } else {
                    studioContext->fileIsOpen = false;
                }
            } else {
                menu_CheckMenus(studioContext, studioPreferences);
                clockOffset = clock();
            }

            if (kb_IsDown(kb_KeyUp)) {
                redraw = edit_CursorUp(studioContext);
            } else if (kb_IsDown(kb_KeyDown)) {
                redraw = edit_CursorDown(studioContext);
            } else if (kb_IsDown(kb_KeyLeft)) {
                redraw = edit_CursorLeft(studioContext);
            } else if (kb_IsDown(kb_KeyRight)) {
                redraw = edit_CursorRight(studioContext);
            } else if (kb_IsDown(kb_KeyMode)) {
                if (!(studioContext->lineStart == 0 && studioContext->row == 0 && studioContext->column == 0)) {
                    redraw = true;
                    edit_CursorLeft(studioContext);
                    edit_Delete(studioContext);
                }
            } else if (kb_IsDown(kb_KeyDel)) {
                if (studioContext->rowDataStart + studioContext->column <= studioContext->openEOF) {
                    redraw = true;
                    edit_Delete(studioContext);
                }
            } else if (kb_IsDown(kb_KeyAlpha)) {
                if (inputMode == INPUT_LOWERCASE) {
                    inputMode = 0;
                } else {
                    inputMode++;
                }

                while (kb_AnyKey());
            } else if (studioContext->fileSize < MAX_FILE_SIZE) {
                if (!keyPressed) {
                    key = util_GetSingleKeyPress();
                }

                inputChar = util_KeyToChar(key, inputMode);
                redraw = util_InsertChar(inputChar, studioContext);
            }

            if (studioContext->column > studioContext->rowLength) {
                studioContext->column = studioContext->rowLength;
            }

            if (!redraw) {
                ui_DrawCursor(studioContext->row, studioContext->column, cursorActive, false);
                spi_endFrame();
            } else {
                redraw = false;
                edit_RedrawEditor(studioContext, studioPreferences);
            }

            if (clock() - clockOffset > CLOCKS_PER_SEC / 3 && !keyPressed) {
                ui_DrawCursor(studioContext->row, studioContext->column, cursorActive, false);
                cursorActive = !cursorActive;
                clockOffset = clock();
            }

            util_WaitBeforeKeypress(&clockOffset, &keyPressed);
        }
    }
}
