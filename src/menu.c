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
#include "asm/misc.h"
#include "gfx/gfx.h"

#include <graphx.h>
#include <fontlibc.h>
#include <fileioc.h>
#include <keypadc.h>
#include <stdint.h>
#include <string.h>
#include <sys/timers.h>

static bool menu_MiniMenu(bool *initialOption, unsigned int x, uint8_t y, unsigned int width, uint8_t height, char *option1, char *option2) {
    gfx_SetDrawScreen(); // Easier to get rid of this way
    ui_DrawMenuBox(x, y, width, height, 0, 2, option1, option2);

    bool optionSelected = false;

    while (!kb_IsDown(kb_KeyClear) && !kb_IsDown(kb_KeyEnter) && !kb_IsDown(kb_Key2nd) && !kb_IsDown(kb_KeyLeft)) {
        kb_Scan();

        if (kb_IsDown(kb_KeyUp) || kb_IsDown(kb_KeyDown)) {
            optionSelected = !optionSelected;
            ui_DrawMenuBox(x, y, width, height, optionSelected, 2, option1, option2);
            while (kb_AnyKey());
        }
    }

    if (kb_IsDown(kb_Key2nd) || kb_IsDown(kb_KeyEnter)) {
        while (kb_AnyKey());
        *initialOption = !optionSelected; // Not sure why it had to be ! but who knows
        gfx_SetDrawBuffer();
        return true; // Something was changed
    }

    gfx_SetDrawBuffer();
    return false; // Something was not changed
}

static void menu_FileOpenRedraw(char *fileNames, unsigned int totalLines, unsigned int fileCount, unsigned int fileStartLoc, uint8_t fileSelected, uint8_t rowsPerScreen, uint8_t boxY, uint8_t boxHeight) {
    if (!fileCount) {
        gfx_SetColor(BACKGROUND);
        gfx_FillRectangle_NoClip(86, 117, 138, 18);

        gfx_SetColor(OUTLINE);
        gfx_Rectangle_NoClip(84, 115, 142, 22);
        gfx_Rectangle_NoClip(85, 116, 140, 20);

        fontlib_SetForegroundColor(TEXT_DEFAULT);
        fontlib_SetCursorPosition(106, 120);
        fontlib_DrawString("No files found");
    } else {
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
}

static void menu_FileOpen(struct context_t *studioContext, char *fileNames, unsigned int fileCount) {
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

        if (kb_Data[7] && (!keyPressed || timer_Get(1) > 3000) && fileCount) {
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

    if (kb_IsDown(kb_KeyClear)) {
        while (kb_AnyKey());
        free(fileNames);
        return; // Return early
    }

    free(studioContext->fileName);
    char *fileOpened = malloc(9);

    strcpy(fileOpened, &fileNames[(fileStartLoc + fileSelected) * 9]);
    studioContext->fileName = fileOpened;
    studioContext->fileIsOpen = true;

    uint8_t file = ti_Open(studioContext->fileName, "r");

    studioContext->lineStart = 0;
    studioContext->newlineStart = 0;
    studioContext->row = 0;
    studioContext->column = 0;

    studioContext->pageDataStart = ti_GetDataPtr(file);
    studioContext->pageDataStart += 2;
    studioContext->rowDataStart = studioContext->pageDataStart;
    studioContext->fileDataStart = studioContext->rowDataStart;
    studioContext->rowLength = files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);

    files_CountLines(studioContext->fileName, &(studioContext->newlineCount), &(studioContext->totalLines));
    studioContext->openEOF = files_GetEOF(studioContext->fileName);

    ti_Close(file);
    free(fileNames);
}

void menu_File(struct context_t *studioContext) {
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
                menu_FileOpen(studioContext, fileNames, fileCount);
                break;
            }
            case 2: // Save file
                break;
            default:
                break;
        }
    }
}

void menu_Compile(struct context_t *studioContext) {
    ui_DrawUIMain(2, studioContext->totalLines, studioContext->lineStart);
    gfx_SwapDraw();

    while (kb_AnyKey()); // Wait for key to be released

    // Do more here later!
}

void menu_Goto(struct context_t *studioContext) {
    ui_DrawUIMain(3, studioContext->totalLines, studioContext->lineStart);
    gfx_SwapDraw();

    while (kb_AnyKey()); // Wait for key to be released

    gfx_SetColor(OUTLINE);
    gfx_FillRectangle_NoClip(101, 207, 71, 16);
    gfx_Rectangle_NoClip(172, 207, 36, 18);
    gfx_Rectangle_NoClip(173, 208, 34, 16);

    gfx_SetColor(BACKGROUND);
    gfx_FillRectangle_NoClip(174, 209, 32, 14);

    fontlib_SetForegroundColor(TEXT_DEFAULT);
    fontlib_SetCursorPosition(104, 210);
    fontlib_DrawString("Goto Line:");
    gfx_BlitBuffer();

    char *input = util_StringInputBox(175, 210, 5, INPUT_NUMBERS, kb_KeyZoom);

    if (input != NULL) {
        int targetLine = misc_StringToInt(input) - 1;

        if (targetLine >= 0 && (unsigned int)targetLine < studioContext->newlineCount) {
            studioContext->row = 0;
            studioContext->column = 0;

            while (studioContext->newlineStart != (unsigned int)targetLine) {
                if ((unsigned int)targetLine < studioContext->newlineStart) {
                    studioContext->newlineStart -= ((*(studioContext->pageDataStart - 1) == '\n') || !(studioContext->lineStart));
                    studioContext->lineStart--;
                    studioContext->pageDataStart = files_PreviousLine(studioContext->pageDataStart, studioContext->fileDataStart);
                    studioContext->rowDataStart = studioContext->pageDataStart;
                    studioContext->rowLength = files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
                } else if (studioContext->lineStart + 14 < studioContext->totalLines) {
                    studioContext->lineStart++;
                    studioContext->pageDataStart = files_NextLine(studioContext->pageDataStart);
                    studioContext->rowDataStart = files_NextLine(studioContext->rowDataStart);
                    studioContext->rowLength = files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
                    studioContext->newlineStart += (*(studioContext->pageDataStart - 1) == '\n');
                } else {
                    for (unsigned int currentLine = studioContext->newlineStart; currentLine < (unsigned int)targetLine;) {
                        studioContext->row++;
                        studioContext->rowDataStart = files_NextLine(studioContext->rowDataStart);
                        studioContext->rowLength = files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
                        currentLine += (*(studioContext->rowDataStart - 1) == '\n');
                    }
                    break; // Ensure it doesn't get stuck in an infinite loop if line is right at the end
                }
            }
        }
    }

    if (kb_IsDown(kb_KeyZoom)) { // Ensure the menu doesn't get opened again immediately
        ui_DrawUIMain(3, studioContext->totalLines, studioContext->lineStart);
        gfx_BlitBuffer();

        while (kb_AnyKey());
    }
}

void menu_Chars(struct context_t *studioContext) {
    ui_DrawUIMain(4, studioContext->totalLines, studioContext->lineStart);
    gfx_SwapDraw();

    while (kb_AnyKey()); // Wait for key to be released

    // Do more here later!
}

static void menu_About(void) {
    gfx_SetColor(BACKGROUND);
    gfx_FillRectangle_NoClip(86, 72, 138, 92);

    gfx_SetColor(OUTLINE);
    gfx_Rectangle_NoClip(84, 56, 142, 110);
    gfx_Rectangle_NoClip(85, 57, 140, 108);
    gfx_FillRectangle_NoClip(86, 58, 138, 14);

    fontlib_SetForegroundColor(TEXT_DEFAULT);
    fontlib_SetCursorPosition(138, 58);
    fontlib_DrawString("About");

    fontlib_SetCursorPosition(87, 73);
    fontlib_DrawString("ez80 Studio");
    fontlib_SetCursorPosition(87, 85);
    fontlib_DrawString("Version: "VERSION_NO);

    gfx_HorizLine_NoClip(87, 98, 136);

    fontlib_SetCursorPosition(87, 100);
    fontlib_DrawString("An ez80 IDE for TI");
    fontlib_SetCursorPosition(87, 112);
    fontlib_DrawString("ez80 calculators.");

    gfx_HorizLine_NoClip(87, 125, 136);

    fontlib_SetCursorPosition(87, 127);
    fontlib_DrawString("\xA9 2023");
    fontlib_SetCursorPosition(87, 139);
    fontlib_DrawString("RoccoLox Programs,");
    fontlib_SetCursorPosition(87, 151);
    fontlib_DrawString("TIny_Hacker.");

    gfx_BlitBuffer();

    while (kb_AnyKey());

    while (!kb_AnyKey());
}

void menu_Settings(struct context_t *studioContext, struct preferences_t *studioPreferences) {
    ui_DrawUIMain(5, studioContext->totalLines, studioContext->lineStart);
    gfx_SwapDraw();

    while (kb_AnyKey()); // Wait for key to be released

    ui_DrawMenuBox(203, 168, 107, 55, 0, 3, "Themes       \xBB", "Highlighting \xBB", "About"); // \xBB is a right arrow icon

    gfx_BlitBuffer(); // Since we saved the "unpressed" button, we bring it back now that it isn't pressed anymore, with the menu

    uint8_t option = 0;

    bool keyPressed = false;
    timer_Enable(1, TIMER_32K, TIMER_NOINT, TIMER_UP);
    timer_Set(1, 0);

    while (!kb_IsDown(kb_KeyClear) && !kb_IsDown(kb_KeyGraph)) {
        kb_Scan();

        if (!kb_AnyKey()) {
            keyPressed = false;
            timer_Set(1, 0);
        }

        if ((kb_Data[7] || kb_IsDown(kb_KeyEnter) || kb_IsDown(kb_Key2nd)) && (!keyPressed || timer_Get(1) > 3000)) {
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

            if (kb_IsDown(kb_KeyRight) || kb_IsDown(kb_KeyEnter) || kb_IsDown(kb_Key2nd)) {
                switch (option) {
                    case 0: // Themes
                        if (menu_MiniMenu(&(studioPreferences->theme), 158, 151, 47, 40, "Dark", "Light")) {

                            if (studioPreferences->theme) {
                                gfx_SetPalette(darkPalette, sizeof_darkPalette, 0);
                            } else {
                                gfx_SetPalette(lightPalette, sizeof_lightPalette, 0);
                            }

                            return; // Exit menu entirely
                        }

                        break;
                    case 1: // Highlighting
                        if (menu_MiniMenu(&(studioPreferences->highlighting), 172, 168, 33, 40, "On", "Off")) {
                            return;
                        }

                        break;
                    case 2: // About
                        if (!kb_IsDown(kb_KeyRight)) { // Don't open with the right arrow like the other menus
                            menu_About();
                            return;
                        }

                        break;
                }
            }

            ui_DrawMenuBox(203, 168, 107, 55, option, 3, "Themes       \xBB", "Highlighting \xBB", "About");

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
