/**
 * --------------------------------------
 * 
 * eZ80 Studio Source Code - utility.c
 * By RoccoLox Programs and TIny_Hacker
 * Copyright 2022 - 2024
 * License: GPL-3.0
 * 
 * --------------------------------------
**/

#include "assembler.h"
#include "edit.h"
#include "utility.h"
#include "ui.h"
#include "menu.h"
#include "defines.h"
#include "asm/files.h"
#include "asm/misc.h"
#include "asm/spi.h"

#include <graphx.h>
#include <keypadc.h>
#include <fontlibc.h>
#include <time.h>

void edit_RedrawEditor(struct context_t *studioContext, struct preferences_t *studioPreferences) {
    asm_spi_BeginFrame();
    gfx_ZeroScreen();

    if (studioContext->fileIsOpen) {
        ui_DrawUIMain(0, studioContext->totalLines, studioContext->lineStart);
        ui_UpdateText(studioContext, studioPreferences, UPDATE_ALL);
        ui_DrawCursor(studioContext->row, studioContext->column, true, false);
        gfx_SetColor(OUTLINE);
        fontlib_SetForegroundColor(TEXT_DEFAULT);
        fontlib_SetCursorPosition(312, 0);
        fontlib_DrawGlyph("1Aa"[studioContext->inputMode]);
        gfx_Rectangle_NoClip(312, 12, 8, 2);
    } else {
        ui_NoFile();
    }

    asm_spi_EndFrame();
}

static void edit_Scroll(struct context_t *studioContext, struct preferences_t *studioPreferences, uint8_t direction) {
    gfx_SetClipRegion(0, 0, 310, 223);

    if (direction == UPDATE_TOP) {
        gfx_ShiftDown(16);
    } else {
        gfx_ShiftUp(16);
    }

    ui_UpdateText(studioContext, studioPreferences, direction);
    gfx_SetClipRegion(0, 0, 320, 240);
    ui_DrawScrollbar(312, 0, 223, studioContext->totalLines, studioContext->lineStart, 14);
}

static bool edit_CursorUp(struct context_t *studioContext) {
    if (studioContext->row) {
        studioContext->row--;
        studioContext->rowDataStart = asm_files_PreviousLine(studioContext->rowDataStart, studioContext->openEOF);
        studioContext->rowLength = asm_files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
    } else if (studioContext->lineStart) {
        studioContext->newlineStart -= ((*(studioContext->pageDataStart - 1) == '\n') || !(studioContext->lineStart));
        studioContext->lineStart--;
        studioContext->pageDataStart = asm_files_PreviousLine(studioContext->pageDataStart, studioContext->openEOF);
        studioContext->rowDataStart = studioContext->pageDataStart;
        studioContext->rowLength = asm_files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
        return true;
    } else {
        studioContext->column = 0;
    }

    return false;
}

static bool edit_CursorDown(struct context_t *studioContext) {
    if (studioContext->row < 13 && studioContext->lineStart + studioContext->row + 1 != studioContext->totalLines) {
        studioContext->row++;
        studioContext->rowDataStart = asm_files_NextLine(studioContext->rowDataStart);
        studioContext->rowLength = asm_files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
    } else if (studioContext->lineStart + 14 < studioContext->totalLines) {
        studioContext->lineStart++;
        studioContext->pageDataStart = asm_files_NextLine(studioContext->pageDataStart);
        studioContext->rowDataStart = asm_files_NextLine(studioContext->rowDataStart);
        studioContext->rowLength = asm_files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
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
            studioContext->rowDataStart = asm_files_PreviousLine(studioContext->rowDataStart, studioContext->openEOF);
            studioContext->rowLength = asm_files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
            studioContext->column = studioContext->rowLength;
        } else if (studioContext->lineStart) {
            studioContext->lineStart--;
            studioContext->pageDataStart = asm_files_PreviousLine(studioContext->pageDataStart, studioContext->openEOF);
            studioContext->rowDataStart = studioContext->pageDataStart;
            studioContext->rowLength = asm_files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
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
            studioContext->rowDataStart = asm_files_NextLine(studioContext->rowDataStart);
            studioContext->rowLength = asm_files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
            studioContext->column = 0;
        } else if (studioContext->lineStart + 14 < studioContext->totalLines) {
            studioContext->lineStart++;
            studioContext->pageDataStart = asm_files_NextLine(studioContext->pageDataStart);
            studioContext->rowDataStart = asm_files_NextLine(studioContext->rowDataStart);
            studioContext->rowLength = asm_files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
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

    asm_files_DeleteChar(studioContext->rowDataStart + studioContext->column, studioContext->openEOF - (studioContext->rowDataStart + studioContext->column - 1));
    studioContext->openEOF--;
    studioContext->fileSize--;

    asm_files_CountLines(&(studioContext->newlineCount), &(studioContext->totalLines), studioContext->openEOF);

    if (studioContext->lineStart && studioContext->lineStart + 12 >= studioContext->totalLines - 1) {
        studioContext->row++;
        studioContext->lineStart--;
        studioContext->pageDataStart = asm_files_PreviousLine(studioContext->pageDataStart, studioContext->openEOF);
        studioContext->newlineStart -= ((*(studioContext->pageDataStart - 1) == '\n') || !(studioContext->lineStart));
    }

    studioContext->rowLength = asm_files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
}

void edit_OpenEditor(struct context_t *studioContext, struct preferences_t *studioPreferences) {
    while (kb_AnyKey());

    bool keyPressed = false;
    bool cursorActive = true;
    bool redraw = false;
    bool updateHighlight = false;

    uint8_t inputChar = '\0';

    studioContext->fileIsSaved = true;

    asm_spi_BeginFrame();
    edit_RedrawEditor(studioContext, studioPreferences);
    asm_spi_EndFrame();

    clock_t clockOffset = clock(); // Keep track of an offset for timer stuff

    while (studioContext->fileIsOpen) {
        kb_Scan();

        if (!kb_AnyKey() && keyPressed) {
            keyPressed = false;
            updateHighlight = studioPreferences->highlighting; // Update the highlighting a bit later if it's enabled
            clockOffset = clock();
        }

        if (updateHighlight && !keyPressed && clock() - clockOffset > CLOCKS_PER_SEC / 3.5) {
            updateHighlight = false;
            asm_spi_BeginFrame();
            edit_RedrawEditor(studioContext, studioPreferences);
            asm_spi_EndFrame();
        }

        if (kb_AnyKey() && (!keyPressed || clock() - clockOffset > CLOCKS_PER_SEC / 32)) {
            clockOffset = clock();
            cursorActive = true;

            asm_spi_BeginFrame();

            if (kb_IsDown(kb_KeyClear)) {
                if (!studioContext->fileIsSaved) {
                    asm_spi_BeginFrame();
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
                    asm_spi_EndFrame();

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
            } if (kb_IsDown(kb_KeyYequ)) {
                menu_File(studioContext, studioPreferences);
                edit_RedrawEditor(studioContext, studioPreferences);
                while (kb_AnyKey());
            } else if (kb_IsDown(kb_KeyWindow)) {
                uint8_t errorCode = assembler_Main(studioContext);
                edit_RedrawEditor(studioContext, studioPreferences);
                menu_Error(errorCode);
                edit_RedrawEditor(studioContext, studioPreferences);
                while (kb_AnyKey());
            } else if (kb_IsDown(kb_KeyZoom)) {
                menu_Goto(studioContext);
                edit_RedrawEditor(studioContext, studioPreferences);
                while (kb_AnyKey());
            } else if (kb_IsDown(kb_KeyTrace)) {
                char insert = menu_Chars(studioContext);

                if (studioContext->fileSize < MAX_FILE_SIZE && studioContext->fileIsOpen) {
                    util_InsertChar(insert, studioContext);
                }

                edit_RedrawEditor(studioContext, studioPreferences);
                while (kb_AnyKey());
            } else if (kb_IsDown(kb_KeyGraph)) {
                menu_Settings(studioContext, studioPreferences);
                edit_RedrawEditor(studioContext, studioPreferences);
                while (kb_AnyKey());
            } else if (kb_IsDown(kb_KeyUp)) {
                ui_DrawCursor(studioContext->row, studioContext->column, cursorActive, true); // Erase old cursor

                if (edit_CursorUp(studioContext)) {
                    edit_Scroll(studioContext, studioPreferences, UPDATE_TOP);
                }
            } else if (kb_IsDown(kb_KeyDown)) {
                ui_DrawCursor(studioContext->row, studioContext->column, cursorActive, true);

                if (edit_CursorDown(studioContext)) {
                    edit_Scroll(studioContext, studioPreferences, UPDATE_BOTTOM);
                }
            } else if (kb_IsDown(kb_KeyLeft)) {
                ui_DrawCursor(studioContext->row, studioContext->column, cursorActive, true); // Erase old cursor

                if (edit_CursorLeft(studioContext)) {
                    edit_Scroll(studioContext, studioPreferences, UPDATE_TOP);
                }
            } else if (kb_IsDown(kb_KeyRight)) {
                ui_DrawCursor(studioContext->row, studioContext->column, cursorActive, true); // Erase old cursor
                if (edit_CursorRight(studioContext)) {
                    edit_Scroll(studioContext, studioPreferences, UPDATE_BOTTOM);
                }
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
                if (studioContext->inputMode == INPUT_LOWERCASE) {
                    studioContext->inputMode = 0;
                } else {
                    studioContext->inputMode += 1;
                }

                gfx_SetColor(BACKGROUND);
                gfx_FillRectangle_NoClip(313, 2, 5, 8);
                fontlib_SetForegroundColor(TEXT_DEFAULT);
                fontlib_SetCursorPosition(312, 0);
                fontlib_DrawGlyph("1Aa"[studioContext->inputMode]);
                while (kb_AnyKey());
            } else if (studioContext->fileSize < MAX_FILE_SIZE && !redraw) {
                if (!keyPressed) {
                    inputChar = asm_misc_GetCharFromKey(studioContext->inputMode);
                }

                redraw = util_InsertChar(inputChar, studioContext);
            }

            //dbg_printf("-----\nfileIsOpen: %d\nfileIsSaved: %d\npageDataStart: %p\nrowDataStart: %p\nfileName: %s\nfileSize: %d\nopenEOF: %p\nnewlineCount: %d\ntotalLines: %d\nnewlineStart: %d\nlineStart: %d\nrow: %d\ncolumn: %d\nrowLength: %d\n-----\n", studioContext->fileIsOpen, studioContext->fileIsSaved, studioContext->pageDataStart, studioContext->rowDataStart, studioContext->fileName, studioContext->fileSize, studioContext->openEOF, studioContext->newlineCount, studioContext->totalLines, studioContext->newlineStart, studioContext->lineStart, studioContext->row, studioContext->column, studioContext->rowLength);

            if (studioContext->column > studioContext->rowLength) {
                studioContext->column = studioContext->rowLength;
            }

            if (!redraw) {
                ui_DrawCursor(studioContext->row, studioContext->column, cursorActive, false);
                asm_spi_EndFrame();
            } else {
                redraw = false;
                edit_RedrawEditor(studioContext, studioPreferences);
            }

            util_WaitBeforeKeypress(&clockOffset, &keyPressed);
        }

        if (clock() - clockOffset > CLOCKS_PER_SEC / 3 && !kb_AnyKey()) {
            ui_DrawCursor(studioContext->row, studioContext->column, cursorActive, false);
            asm_spi_EndFrame();
            cursorActive = !cursorActive;
            clockOffset = clock();
        }
    }
}
