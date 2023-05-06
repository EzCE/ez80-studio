/**
 * --------------------------------------
 * 
 * ez80 Studio Source Code - utility.c
 * By RoccoLox Programs and TIny_Hacker
 * Copyright 2022 - 2023
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

#include <graphx.h>
#include <keypadc.h>
#include <fontlibc.h>
#include <sys/timers.h>

static void edit_RedrawEditor(struct context_t *studioContext, struct preferences_t *studioPreferences) {
    gfx_ZeroScreen();
    ui_DrawUIMain(0, studioContext->totalLines, studioContext->lineStart);
    ui_UpdateAllText(studioContext, studioPreferences);
    ui_DrawCursor(studioContext->row, studioContext->column, true, false);
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

    timer_Enable(1, TIMER_32K, TIMER_NOINT, TIMER_UP);
    timer_Set(1, 0);

    edit_RedrawEditor(studioContext, studioPreferences);
    gfx_BlitBuffer();

    while (studioContext->fileIsOpen) {
        kb_Scan();

        if (!kb_AnyKey() && keyPressed) {
            keyPressed = false;
            timer_Set(1, 0);
        }

        if (kb_IsDown(kb_KeyClear)) {
            if (!studioContext->fileIsSaved) {
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
                gfx_BlitBuffer();

                if (menu_YesNo(83, 136, 71)) {
                    studioContext->fileIsOpen = false;
                } else {
                    redraw = true;
                    while (kb_AnyKey());
                }
            } else {
                studioContext->fileIsOpen = false;
            }
        } else if (kb_IsDown(kb_KeyYequ) ||
            kb_IsDown(kb_KeyWindow) ||
            kb_IsDown(kb_KeyZoom) ||
            kb_IsDown(kb_KeyTrace) ||
            kb_IsDown(kb_KeyGraph)) {

            if (kb_IsDown(kb_KeyYequ)) {
                menu_File(studioContext, studioPreferences);
                redraw = true;
            } else if (kb_IsDown(kb_KeyWindow)) {
                menu_Compile(studioContext);
                redraw = true;
            } else if (kb_IsDown(kb_KeyZoom)) {
                menu_Goto(studioContext);
                redraw = true;
            } else if (kb_IsDown(kb_KeyTrace)) {
                menu_Chars(studioContext);
                redraw = true;
            } else if (kb_IsDown(kb_KeyGraph)) {
                menu_Settings(studioContext, studioPreferences);
                redraw = true;
            }

            timer_Set(1, 0);
        }

        if (kb_AnyKey() && (!keyPressed || timer_Get(1) > 3000)) {
            cursorActive = true;

            ui_DrawCursor(studioContext->row, studioContext->column, cursorActive, true); // Erase old cursor

            if (kb_IsDown(kb_KeyUp)) {
                if (studioContext->row) {
                    studioContext->row--;
                    studioContext->rowDataStart = files_PreviousLine(studioContext->rowDataStart, studioContext->fileDataStart, studioContext->openEOF);
                    studioContext->rowLength = files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
                } else if (studioContext->lineStart) {
                    redraw = true;
                    studioContext->newlineStart -= ((*(studioContext->pageDataStart - 1) == '\n') || !(studioContext->lineStart));
                    studioContext->lineStart--;
                    studioContext->pageDataStart = files_PreviousLine(studioContext->pageDataStart, studioContext->fileDataStart, studioContext->openEOF);
                    studioContext->rowDataStart = studioContext->pageDataStart;
                    studioContext->rowLength = files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
                } else {
                    studioContext->column = 0;
                }
            } else if (kb_IsDown(kb_KeyDown)) {
                if (studioContext->row < 13 && studioContext->lineStart + studioContext->row + 1 != studioContext->totalLines) {
                    studioContext->row++;
                    studioContext->rowDataStart = files_NextLine(studioContext->rowDataStart);
                    studioContext->rowLength = files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
                } else if (studioContext->lineStart + 14 < studioContext->totalLines) {
                    redraw = true;
                    studioContext->lineStart++;
                    studioContext->pageDataStart = files_NextLine(studioContext->pageDataStart);
                    studioContext->rowDataStart = files_NextLine(studioContext->rowDataStart);
                    studioContext->rowLength = files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
                    studioContext->newlineStart += (*(studioContext->pageDataStart - 1) == '\n');
                } else {
                    studioContext->column = studioContext->rowLength;
                }
            } else if (kb_IsDown(kb_KeyLeft)) {
                if (studioContext->column) {
                    studioContext->column--;
                } else {
                    if (studioContext->row) {
                        studioContext->row--;
                        studioContext->rowDataStart = files_PreviousLine(studioContext->rowDataStart, studioContext->fileDataStart, studioContext->openEOF);
                        studioContext->rowLength = files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
                        studioContext->column = studioContext->rowLength;
                    } else if (studioContext->lineStart) {
                        redraw = true;
                        studioContext->lineStart--;
                        studioContext->pageDataStart = files_PreviousLine(studioContext->pageDataStart, studioContext->fileDataStart, studioContext->openEOF);
                        studioContext->rowDataStart = studioContext->pageDataStart;
                        studioContext->rowLength = files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
                        studioContext->column = studioContext->rowLength;
                        studioContext->newlineStart -= ((*(studioContext->pageDataStart - 1) == '\n') || !(studioContext->lineStart));
                    }
                }
            } else if (kb_IsDown(kb_KeyRight)) {
                if (studioContext->column < studioContext->rowLength) {
                    studioContext->column++;
                } else {
                    if (studioContext->row < 13 && studioContext->lineStart + studioContext->row + 1 != studioContext->totalLines) {
                        studioContext->row++;
                        studioContext->rowDataStart = files_NextLine(studioContext->rowDataStart);
                        studioContext->rowLength = files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
                        studioContext->column = 0;
                    } else if (studioContext->lineStart + 14 < studioContext->totalLines) {
                        redraw = true;
                        studioContext->lineStart++;
                        studioContext->pageDataStart = files_NextLine(studioContext->pageDataStart);
                        studioContext->rowDataStart = files_NextLine(studioContext->rowDataStart);
                        studioContext->rowLength = files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
                        studioContext->column = 0;
                        studioContext->newlineStart += (*(studioContext->pageDataStart - 1) == '\n');
                    }
                }
            } else if (kb_IsDown(kb_KeyMode) && !(studioContext->lineStart == 0 && studioContext->row == 0 && studioContext->column == 0)) {
                if (studioContext->fileIsSaved) {
                    studioContext->fileIsSaved = false;
                }

                redraw = true;

                files_DeleteChar(studioContext->rowDataStart + studioContext->column - 1, studioContext->openEOF - (studioContext->rowDataStart + studioContext->column - 1));
                studioContext->openEOF--;
                studioContext->fileSize--;

                if (studioContext->column) {
                    studioContext->column--;
                } else {
                    if (studioContext->lineStart + studioContext->row >= studioContext->totalLines - 1) {
                        studioContext->lineStart--;
                        studioContext->pageDataStart = files_PreviousLine(studioContext->pageDataStart, studioContext->fileDataStart, studioContext->openEOF);
                        studioContext->rowDataStart = files_PreviousLine(studioContext->rowDataStart, studioContext->fileDataStart, studioContext->openEOF);
                        studioContext->rowLength = files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
                        studioContext->column = studioContext->rowLength;
                        studioContext->newlineStart -= ((*(studioContext->pageDataStart - 1) == '\n') || !(studioContext->lineStart));
                    } else if (studioContext->row) {
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
                    }
                }

                files_CountLines(studioContext->fileDataStart, &(studioContext->newlineCount), &(studioContext->totalLines), studioContext->openEOF);
            } else if (kb_IsDown(kb_KeyDel) && studioContext->rowDataStart + studioContext->column <= studioContext->openEOF) {
                if (studioContext->fileIsSaved) {
                    studioContext->fileIsSaved = false;
                }

                redraw = true;

                files_DeleteChar(studioContext->rowDataStart + studioContext->column, studioContext->openEOF - (studioContext->rowDataStart + studioContext->column - 1));
                studioContext->openEOF--;
                studioContext->fileSize--;

                files_CountLines(studioContext->fileDataStart, &(studioContext->newlineCount), &(studioContext->totalLines), studioContext->openEOF);

                if (studioContext->lineStart + 12 >= studioContext->totalLines - 1) {
                    studioContext->row++;
                    studioContext->lineStart--;
                    studioContext->pageDataStart = files_PreviousLine(studioContext->pageDataStart, studioContext->fileDataStart, studioContext->openEOF);
                    studioContext->rowLength = files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
                    studioContext->newlineStart -= ((*(studioContext->pageDataStart - 1) == '\n') || !(studioContext->lineStart));
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

                if (inputChar) {
                    if (studioContext->fileIsSaved) {
                        studioContext->fileIsSaved = false;
                    }

                    redraw = true;

                    files_InsertChar(inputChar, studioContext->openEOF, studioContext->openEOF - (studioContext->rowDataStart + studioContext->column) + 1);

                    studioContext->fileSize++;
                    studioContext->openEOF++;

                    files_CountLines(studioContext->fileDataStart, &(studioContext->newlineCount), &(studioContext->totalLines), studioContext->openEOF);
                    studioContext->rowLength = files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);

                    if (inputChar == '\n') {
                        studioContext->column = 0;

                        if (studioContext->row < 13 && studioContext->lineStart + studioContext->row + 1 != studioContext->totalLines) {
                            studioContext->row++;
                            studioContext->rowDataStart = files_NextLine(studioContext->rowDataStart);
                            studioContext->rowLength = files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
                        } else {
                            redraw = true;
                            studioContext->lineStart++;
                            studioContext->pageDataStart = files_NextLine(studioContext->pageDataStart);
                            studioContext->rowDataStart = files_NextLine(studioContext->rowDataStart);
                            studioContext->rowLength = files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
                            studioContext->newlineStart += (*(studioContext->pageDataStart - 1) == '\n');
                        }
                    } else {
                        if (studioContext->column < studioContext->rowLength) {
                            studioContext->column++;
                        } else {
                            if (studioContext->row < 13 && studioContext->lineStart + studioContext->row + 1 != studioContext->totalLines) {
                                studioContext->row++;
                                studioContext->rowDataStart = files_NextLine(studioContext->rowDataStart);
                                studioContext->rowLength = files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
                                studioContext->column = 1; // Skip the new character
                            } else if (studioContext->lineStart + 14 < studioContext->totalLines) {
                                redraw = true;
                                studioContext->lineStart++;
                                studioContext->pageDataStart = files_NextLine(studioContext->pageDataStart);
                                studioContext->rowDataStart = files_NextLine(studioContext->rowDataStart);
                                studioContext->rowLength = files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
                                studioContext->column = 1;
                                studioContext->newlineStart += (*(studioContext->pageDataStart - 1) == '\n');
                            }
                        }
                    }
                }
            }

            if (studioContext->column > studioContext->rowLength) {
                studioContext->column = studioContext->rowLength;
            }

            if (!redraw) {
                ui_DrawCursor(studioContext->row, studioContext->column, cursorActive, false);
                gfx_BlitBuffer();
            }

            if (!keyPressed) {
                while (timer_Get(1) < 9000 && kb_AnyKey()) {
                    kb_Scan();
                }
            }

            keyPressed = true;
            timer_Set(1, 0);
        }

        if (timer_Get(1) > 10000 && !keyPressed) {
            ui_DrawCursor(studioContext->row, studioContext->column, cursorActive, false);
            cursorActive = !cursorActive;
            timer_Set(1, 0);

            gfx_BlitBuffer();
        }

        if (redraw) {
            redraw = false;
            edit_RedrawEditor(studioContext, studioPreferences);
            gfx_BlitBuffer();
        }
    }
}
