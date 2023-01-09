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
#include "asm/files.h"

#include <graphx.h>
#include <keypadc.h>
#include <sys/timers.h>

static void edit_RedrawEditor(struct context *studioContext) {
    gfx_ZeroScreen();
    ui_DrawUIMain(0, studioContext->totalLines, studioContext->lineStart);
    ui_UpdateAllText(studioContext);
}

void edit_OpenEditor(struct context *studioContext) {
    bool keyPressed = false;
    bool cursorActive = true;
    bool redraw = false;

    timer_Enable(1, TIMER_32K, TIMER_NOINT, TIMER_UP);
    timer_Set(1, 0);

    edit_RedrawEditor(studioContext);
    gfx_BlitBuffer();

    while (!kb_IsDown(kb_KeyClear)) {
        kb_Scan();

        if (!kb_AnyKey() && keyPressed) {
            keyPressed = false;
            timer_Set(1, 0);
        }

        if (kb_Data[7] && (!keyPressed || timer_Get(1) > 3000)) {
            cursorActive = true;

            ui_DrawCursor(studioContext->row, studioContext->column, cursorActive, true); // Erase old cursor

            if (kb_IsDown(kb_KeyUp)) {
                if (studioContext->row) {
                    studioContext->row--;
                    studioContext->rowDataStart = files_PreviousLine(studioContext->rowDataStart);
                    studioContext->rowLength = files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
                } else if (studioContext->lineStart) {
                    redraw = true;
                    studioContext->lineStart--;
                    studioContext->pageDataStart = files_PreviousLine(studioContext->pageDataStart);
                    studioContext->rowDataStart = files_PreviousLine(studioContext->rowDataStart);
                    studioContext->rowLength = files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
                } else {
                    studioContext->column = 0;
                }
            } else if (kb_IsDown(kb_KeyDown)) {
                if (studioContext->row < 13 && studioContext->lineStart + studioContext->row != studioContext->totalLines) {
                    studioContext->row++;
                    studioContext->rowDataStart = files_NextLine(studioContext->rowDataStart);
                    studioContext->rowLength = files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
                } else if (studioContext->lineStart + 14 < studioContext->totalLines) {
                    redraw = true;
                    studioContext->lineStart++;
                    studioContext->pageDataStart = files_NextLine(studioContext->pageDataStart);
                    studioContext->rowDataStart = files_NextLine(studioContext->rowDataStart);
                    studioContext->rowLength = files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
                } else {
                    studioContext->column = studioContext->rowLength;
                }
            }

            if (kb_IsDown(kb_KeyLeft)) {
                if (studioContext->column) {
                    studioContext->column--;
                } else {
                    if (studioContext->row) {
                        studioContext->row--;
                        studioContext->rowDataStart = files_PreviousLine(studioContext->rowDataStart);
                        studioContext->rowLength = files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
                        studioContext->column = studioContext->rowLength;
                    } else if (studioContext->lineStart) {
                        redraw = true;
                        studioContext->lineStart--;
                        studioContext->pageDataStart = files_PreviousLine(studioContext->pageDataStart);
                        studioContext->rowDataStart = files_PreviousLine(studioContext->rowDataStart);
                        studioContext->rowLength = files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
                        studioContext->column = studioContext->rowLength;
                    }
                }
            } else if (kb_IsDown(kb_KeyRight)) {
                if (studioContext->column < studioContext->rowLength) {
                    studioContext->column++;
                } else {
                    if (studioContext->row < 13 && studioContext->lineStart + studioContext->row != studioContext->totalLines) {
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
                    }
                }
            }

            if (studioContext->column > studioContext->rowLength) {
                studioContext->column = studioContext->rowLength;
            }

            ui_DrawCursor(studioContext->row, studioContext->column, cursorActive, false);
            gfx_BlitBuffer();

            if (!keyPressed) {
                while (timer_Get(1) < 9000 && kb_Data[7]) {
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
        } else if (keyPressed) {
            ui_DrawCursor(studioContext->row, studioContext->column, cursorActive, false);
            gfx_BlitBuffer();
        }

        if (redraw) {
            redraw = false;
            edit_RedrawEditor(studioContext);
            gfx_BlitBuffer();
        }
    }
}
