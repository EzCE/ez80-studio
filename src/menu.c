/**
 * --------------------------------------
 * 
 * ez80 Studio Source Code - menu.c
 * By RoccoLox Programs and TIny_Hacker
 * Copyright 2022 - 2023
 * License: GPL-3.0
 * 
 * --------------------------------------
**/

#include "defines.h"
#include "menu.h"
#include "utility.h"
#include "ui.h"
#include "asm/files.h"

#include <graphx.h>
#include <fontlibc.h>
#include <fileioc.h>
#include <keypadc.h>
#include <stdint.h>
#include <string.h>
#include <sys/timers.h>

static void menu_FileOpenRedraw(char *fileNames, unsigned int totalLines, unsigned int fileCount, unsigned int fileStartLoc, uint8_t fileSelected, uint8_t rowsPerScreen, uint8_t boxY, uint8_t boxHeight) {
    gfx_SetColor(BACKGROUND);
    gfx_FillRectangle_NoClip(86, boxY + 16, 128, boxHeight - 18);

    gfx_SetColor(OUTLINE);
    gfx_FillRectangle_NoClip(87 + fileSelected % 2 * 64, boxY + 17 + fileSelected / 2 * 17, 62, 16); // Cursor over selected item in menu

    unsigned int fileNameDrawing = fileStartLoc * 9; 

    for (uint8_t drawRow = 0; drawRow < rowsPerScreen; drawRow++) {
        fontlib_SetCursorPosition(90, boxY + 19 + drawRow * 17);
        fontlib_DrawString(&fileNames[fileNameDrawing]);
        fileNameDrawing += 9;

        if (fileNameDrawing == fileCount * 9) {
            break;
        }

        fontlib_SetCursorPosition(154, boxY + 19 + drawRow * 17);
        fontlib_DrawString(&fileNames[fileNameDrawing]);
        fileNameDrawing += 9;
    }

    ui_DrawScrollbar(216, boxY + 16, boxHeight - 18, totalLines, fileStartLoc / 2, rowsPerScreen);
}

static char *menu_FileOpen(char *fileNames, unsigned int fileCount) {
    while (kb_AnyKey());

    unsigned int rowsPerScreen = (fileCount + 1) / 2;

    if (rowsPerScreen > 8) {
        rowsPerScreen = 8;
    }

    uint8_t boxY = 101 - rowsPerScreen * 17 / 2;
    uint8_t boxHeight =  19 + rowsPerScreen * 17;

    unsigned int fileStartLoc = 0; // It's CEaShell all over again
    unsigned int fileSelected = 0;

    gfx_SetColor(OUTLINE);
    gfx_Rectangle_NoClip(84, boxY, 142, boxHeight);
    gfx_Rectangle_NoClip(85, boxY + 1, 140, boxHeight - 2);
    gfx_Rectangle_NoClip(214, boxY + 16, 2, boxHeight - 18);
    gfx_FillRectangle_NoClip(86, boxY + 2, 138, 14);
    fontlib_SetCursorPosition(122, boxY + 2);
    fontlib_DrawString("Open file");

    menu_FileOpenRedraw(fileNames, (fileCount + 1) / 2, fileCount, 0, 0, rowsPerScreen, boxY, boxHeight);

    gfx_BlitBuffer();

    bool keyPressed = false;
    timer_Enable(1, TIMER_32K, TIMER_NOINT, TIMER_UP);
    timer_Set(1, 0);

    unsigned int bottomItem = fileCount + fileCount % 2;

    while (!kb_IsDown(kb_KeyClear) && !kb_IsDown(kb_Key2nd) && !kb_IsDown(kb_KeyEnter)) {
        kb_Scan();

        if (!kb_AnyKey()) {
            keyPressed = false;
            timer_Set(1, 0);
        }

        if (kb_Data[7] && (!keyPressed || timer_Get(1) > 3000)) {
            if (kb_IsDown(kb_KeyUp)) {
                if (fileSelected < 2) {
                    if (fileStartLoc) {
                        fileStartLoc -= 2;
                    } else {
                        fileStartLoc = (bottomItem - rowsPerScreen * 2);
                        fileSelected += rowsPerScreen * 2 - 2; 

                        if (fileStartLoc + fileSelected + 1 > fileCount) {
                            fileSelected -= 2;
                        }
                    }
                } else {
                    fileSelected -= 2;
                }
            } else if (kb_IsDown(kb_KeyDown)) {
                if (fileSelected + 3 > rowsPerScreen * 2) {
                    if (fileStartLoc < bottomItem - rowsPerScreen * 2) {
                        fileStartLoc += 2;
                    } else if (fileStartLoc + fileSelected + 2 >= fileCount) {
                        fileStartLoc = 0;
                        fileSelected -= rowsPerScreen * 2 - 2;
                    }
                } else if (fileStartLoc + fileSelected + 1 == fileCount - 1) {
                    fileSelected++;
                } else {
                    fileSelected += 2;
                }
            }

            if (kb_IsDown(kb_KeyLeft)) {
                if (fileSelected) {
                    fileSelected--;
                } else {
                    if (fileStartLoc) {
                        fileSelected = 1;
                        fileStartLoc -= 2;
                    } else {
                        fileStartLoc = bottomItem - rowsPerScreen * 2;
                        fileSelected = fileCount - fileStartLoc - 1;
                    }
                }
            } else if (kb_IsDown(kb_KeyRight)) {
                if (fileStartLoc + fileSelected + 1 == fileCount && fileSelected == rowsPerScreen * 2 - 2) {
                    fileSelected--;
                } else if (fileSelected + 2 > rowsPerScreen * 2) {
                    if (fileStartLoc + fileSelected + 1 != fileCount) {
                        fileStartLoc += 2;
                        fileSelected = rowsPerScreen * 2 - 2;
                    } else {
                        fileStartLoc = 0;
                        fileSelected = 0;
                    }
                } else {
                    fileSelected++;
                }
            }

            menu_FileOpenRedraw(fileNames, (fileCount + 1) / 2, fileCount, fileStartLoc, fileSelected, rowsPerScreen, boxY, boxHeight);

            gfx_BlitBuffer();

            if (!keyPressed) {
                while (timer_Get(1) < 9000 && kb_Data[7]) {
                    kb_Scan();
                }
            }

            keyPressed = true;
            timer_Set(1,0);
        }
    }

    char *fileOpened = NULL;

    if (kb_IsDown(kb_KeyEnter) || kb_IsDown(kb_Key2nd)) {
        fileOpened = &fileNames[(fileStartLoc + fileSelected) * 9];
    }

    free(fileNames);

    return fileOpened;
}

void menu_File(struct context *studioContext) {
    ui_DrawUIMain(1, studioContext->totalLines, studioContext->lineStart);
    gfx_SwapDraw();

    while (kb_AnyKey()); // Wait for key to be released

    ui_DrawMenuBox(0, 168, 73, 55, 0, 3, "New file", "Open file", "Save file");

    gfx_BlitBuffer(); // Since we saved the "unpressed" button, we bring it back now that it isn't pressed anymore, with the menu

    uint8_t option = 0;

    bool keyPressed = false;
    timer_Enable(1, TIMER_32K, TIMER_NOINT, TIMER_UP);
    timer_Set(1, 0);

    while (!kb_IsDown(kb_KeyClear) && !kb_IsDown(kb_KeyYequ) && !kb_IsDown(kb_Key2nd) && !kb_IsDown(kb_KeyEnter)) {
        kb_Scan();

        if (!kb_AnyKey()) {
            keyPressed = false;
            timer_Set(1, 0);
        }

        if (kb_Data[7] && (!keyPressed || timer_Get(1) > 3000)) {
            if (kb_IsDown(kb_KeyUp)) {
                if (option == 0) { // Loop the cursor
                    option = 2;
                } else {
                    option -= 1;
                }
            } else if (kb_IsDown(kb_KeyDown)) {
                if (option == 2) { // Loop the cursor
                    option = 0;
                } else {
                    option += 1;
                }
            }

            ui_DrawMenuBox(0, 168, 73, 55, option, 3, "New file", "Open file", "Save file");

            gfx_BlitBuffer();

            if (!keyPressed) {
                while (timer_Get(1) < 9000 && kb_Data[7]) {
                    kb_Scan();
                }
            }

            keyPressed = true;
            timer_Set(1,0);
        }
    }

    if (kb_IsDown(kb_KeyYequ)) { // Ensure the menu doesn't get opened again immediately
        ui_DrawUIMain(1, studioContext->totalLines, studioContext->lineStart);
        gfx_BlitBuffer();

        while (kb_AnyKey());
    } else if (kb_IsDown(kb_Key2nd) || kb_IsDown(kb_KeyEnter)) {
        switch (option) {
            case 0: // New file
                break;
            case 1: { // Open file
                unsigned int fileCount = 0;
                char *fileNames = util_GetFiles(&fileCount);
                studioContext->fileName = menu_FileOpen(fileNames, fileCount);
                studioContext->fileIsOpen = true;

                uint8_t file = ti_Open(studioContext->fileName, "r");

                studioContext->pageDataStart = ti_GetDataPtr(file);
                studioContext->pageDataStart += 2;

                files_CountLines(studioContext->fileName, &(studioContext->newlineCount), &(studioContext->totalLines));
                break;
            }
            case 2: // Save file
                break;
            default:
                break;
        }
    }
}

void menu_Compile(struct context *studioContext) {
    ui_DrawUIMain(2, studioContext->totalLines, studioContext->lineStart);
    gfx_SwapDraw();

    while (kb_AnyKey()); // Wait for key to be released

    // Do more here later!
}

void menu_Labels(struct context *studioContext) {
    ui_DrawUIMain(3, studioContext->totalLines, studioContext->lineStart);
    gfx_SwapDraw();

    while (kb_AnyKey()); // Wait for key to be released

    // Do more here later!
}

void menu_Chars(struct context *studioContext) {
    ui_DrawUIMain(4, studioContext->totalLines, studioContext->lineStart);
    gfx_SwapDraw();

    while (kb_AnyKey()); // Wait for key to be released

    // Do more here later!
}

void menu_Settings(struct context *studioContext, struct preferences *studioPreferences) {
    ui_DrawUIMain(5, studioContext->totalLines, studioContext->lineStart);
    gfx_SwapDraw();

    while (kb_AnyKey()); // Wait for key to be released

    ui_DrawMenuBox(255, 202, 55, 21, 0, 1, "Themes");

    gfx_BlitBuffer(); // Since we saved the "unpressed" button, we bring it back now that it isn't pressed anymore, with the menu

    uint8_t option = 0;

    bool keyPressed = false;
    timer_Enable(1, TIMER_32K, TIMER_NOINT, TIMER_UP);
    timer_Set(1, 0);

    while (!kb_IsDown(kb_KeyClear) && !kb_IsDown(kb_KeyGraph) && !kb_IsDown(kb_Key2nd) && !kb_IsDown(kb_KeyEnter)) {
        kb_Scan();

        if (!kb_AnyKey()) {
            keyPressed = false;
            timer_Set(1, 0);
        }

        if (kb_Data[7] && (!keyPressed || timer_Get(1) > 3000)) {
            if (kb_IsDown(kb_KeyUp)) {
                if (option == 0) { // Loop the cursor
                    option = 0;
                } else {
                    option -= 1;
                }
            } else if (kb_IsDown(kb_KeyDown)) {
                if (option == 0) { // Loop the cursor
                    option = 0;
                } else {
                    option += 1;
                }
            }

            ui_DrawMenuBox(255, 202, 55, 21, option, 1, "Themes");

            gfx_BlitBuffer();

            if (!keyPressed) {
                while (timer_Get(1) < 9000 && kb_Data[7]) {
                    kb_Scan();
                }
            }

            keyPressed = true;
            timer_Set(1,0);
        }
    }

    if (kb_IsDown(kb_KeyGraph)) { // Ensure the menu doesn't get opened again immediately
        ui_DrawUIMain(5, studioContext->totalLines, studioContext->lineStart);
        gfx_BlitBuffer();

        while (kb_AnyKey());
    }
}
