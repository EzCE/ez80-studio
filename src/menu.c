/**
 * --------------------------------------
 * 
 * eZ80 Studio Source Code - menu.c
 * By RoccoLox Programs and TIny_Hacker
 * Copyright 2022 - 2024
 * License: GPL-3.0
 * 
 * --------------------------------------
**/

#include "defines.h"
#include "edit.h"
#include "menu.h"
#include "utility.h"
#include "ui.h"
#include "asm/files.h"
#include "asm/misc.h"
#include "asm/spi.h"
#include "gfx/gfx.h"

#include <graphx.h>
#include <fontlibc.h>
#include <fileioc.h>
#include <keypadc.h>
#include <stdint.h>
#include <string.h>

void menu_Error(struct error_t error) {
    asm_spi_BeginFrame();
    gfx_SetColor(OUTLINE);
    gfx_FillRectangle_NoClip(81, 94, 148, 34);
    gfx_SetColor(BACKGROUND);
    gfx_FillRectangle_NoClip(83, 110, 144, 16);
    fontlib_SetForegroundColor(TEXT_DEFAULT);

    if (error.code) {
        if (error.line) {
            fontlib_SetCursorPosition(96, 96);
        } else {
            fontlib_SetCursorPosition(137, 96);
        }

        fontlib_DrawString("Error");

        if (error.line) {
            fontlib_DrawString(" (Line ");
            fontlib_DrawUInt(error.line, 4);
            fontlib_DrawGlyph(')');
        }
    } else {
        fontlib_SetCursorPosition(130, 96);
        fontlib_DrawString("Success");
    }

    switch (error.code) {
        case ERROR_SUCCESS:
            fontlib_SetCursorPosition(90, 112);
            fontlib_DrawString("Operation complete.");
            break;
        case ERROR_UNKNOWN:
            fontlib_SetCursorPosition(128, 112);
            fontlib_DrawString("Unknown.");
            break;
        case ERROR_NO_MEM:
            fontlib_SetCursorPosition(93, 112);
            fontlib_DrawString("Not enough memory.");
            break;
        case ERROR_INVAL_TOK:
            fontlib_SetCursorPosition(86, 112);
            fontlib_DrawString("Invalid instruction.");
            break;
        case ERROR_INVAL_EXPR:
            fontlib_SetCursorPosition(89, 112);
            fontlib_DrawString("Invalid expression.");
            break;
        case ERROR_MAX_SYMBOLS:
            fontlib_SetCursorPosition(96, 112);
            fontlib_DrawString("Too many symbols.");
            break;
        case ERROR_TOO_LARGE:
            fontlib_SetCursorPosition(96, 112);
            fontlib_DrawString("Output too large.");
            break;
        default:
            break;
    }

    asm_spi_EndFrame();

    while(kb_AnyKey());
    while (!kb_IsDown(kb_KeyClear)) {
        kb_Scan();
    }
}

void menu_YesNoRedraw(bool returnVal, unsigned int x, uint8_t y, uint8_t buttonWidth) {
    asm_spi_BeginFrame();
    gfx_SetColor(BACKGROUND);
    gfx_FillRectangle_NoClip(x, y, buttonWidth * 2 + 2, 16);
    gfx_SetColor(OUTLINE);
    gfx_FillRectangle_NoClip(x + (buttonWidth + 2) * !returnVal, y, buttonWidth, 16);
    fontlib_SetCursorPosition(x + (buttonWidth - 21) / 2, y + 2);
    fontlib_DrawString("Yes");
    fontlib_SetCursorPosition(x + buttonWidth + 2 + (buttonWidth - 14) / 2, y + 2);
    fontlib_DrawString("No");
    asm_spi_EndFrame();
}

bool menu_YesNo(unsigned int x, uint8_t y, uint8_t buttonWidth) {
    bool returnVal = true;
    menu_YesNoRedraw(returnVal, x, y, buttonWidth);

    while(kb_AnyKey());

    while (!kb_IsDown(kb_KeyClear) && !kb_IsDown(kb_KeyEnter) && !kb_IsDown(kb_Key2nd)) {
        kb_Scan();

        if (kb_IsDown(kb_KeyLeft) || kb_IsDown(kb_KeyRight)) {
            returnVal = !returnVal;
            menu_YesNoRedraw(returnVal, x, y, buttonWidth);
            while(kb_AnyKey());
        }
    }

    if (kb_IsDown(kb_KeyClear)) {
        while(kb_AnyKey());
        return false;
    }

    while(kb_AnyKey());

    return returnVal;
}

bool menu_Warning(uint8_t warning) {
    asm_spi_BeginFrame();
    gfx_SetColor(OUTLINE);
    gfx_FillRectangle_NoClip(80, 68, 150, 87);
    gfx_SetColor(BACKGROUND);
    gfx_FillRectangle_NoClip(82, 84, 146, 69);
    fontlib_SetForegroundColor(TEXT_DEFAULT);
    fontlib_SetCursorPosition(130, 70);
    fontlib_DrawString("Warning");

    switch (warning) {
        case WARNING_UNSAVED:
            fontlib_SetCursorPosition(85, 85);
            fontlib_DrawString("The currently opened");
            fontlib_SetCursorPosition(85, 96);
            fontlib_DrawString("file has unsaved");
            fontlib_SetCursorPosition(85, 108);
            fontlib_DrawString("changes. Do you wish");
            fontlib_SetCursorPosition(85, 121);
            fontlib_DrawString("to discard them?");
            break;
        case WARNING_EXISTS:
            fontlib_SetCursorPosition(85, 85);
            fontlib_DrawString("A program with this");
            fontlib_SetCursorPosition(85, 96);
            fontlib_DrawString("name already exists.");
            fontlib_SetCursorPosition(85, 108);
            fontlib_DrawString("Do you wish to");
            fontlib_SetCursorPosition(85, 121);
            fontlib_DrawString("overwrite it?");
            break;
    }

    asm_spi_EndFrame();

    return menu_YesNo(83, 136, 71);
}

static bool menu_MiniMenu(bool *initialOption, unsigned int x, uint8_t y, unsigned int width, uint8_t height, char *option1, char *option2) {
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
        return true; // Something was changed
    }

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

static void menu_FileNew(struct context_t *studioContext) {
    while (kb_AnyKey());
    asm_spi_BeginFrame();
    gfx_SetColor(OUTLINE);
    gfx_FillRectangle_NoClip(123, 95, 64, 32);
    gfx_SetColor(BACKGROUND);
    gfx_FillRectangle_NoClip(125, 111, 60, 14);

    fontlib_SetForegroundColor(TEXT_DEFAULT);
    fontlib_SetCursorPosition(127, 97);
    fontlib_DrawString("New file");
    asm_spi_EndFrame();

    char *newFile = util_StringInputBox(126, 112, 9, INPUT_UPPERCASE, kb_KeyClear);

    if (newFile != NULL) {
        if (asm_files_CheckFileExists(newFile, OS_TYPE_APPVAR)) {
            asm_spi_BeginFrame();
            gfx_SetColor(OUTLINE);
            gfx_FillRectangle_NoClip(82, 82, 146, 60);
            gfx_SetColor(BACKGROUND);
            gfx_FillRectangle_NoClip(84, 122, 142, 18);
            fontlib_SetForegroundColor(TEXT_DEFAULT);
            fontlib_SetCursorPosition(85, 84);
            fontlib_DrawString("A file aready exists");
            fontlib_SetCursorPosition(104, 96);
            fontlib_DrawString("with that name.");
            fontlib_SetCursorPosition(110, 108);
            fontlib_DrawString("Overwrite it?");
            asm_spi_EndFrame();

            if(!menu_YesNo(85, 123, 69)) {
                return; // Don't make the file
            }

            ti_DeleteVar(newFile, OS_TYPE_APPVAR);
        }

        uint8_t file = ti_Open(newFile, "w");
        uint16_t header = 0x7AEF;
        ti_Write(&header, 2, 1, file);
        ti_Close(file);

        if (!util_OpenFile(studioContext, newFile)) {
            struct error_t error = {0, ERROR_NO_MEM};
            menu_Error(error);
        }

        //dbg_printf("-----\nfileIsOpen: %d\nfileIsSaved: %d\npageDataStart: %p\nrowDataStart: %p\nfileName: %s\nfileSize: %d\nopenEOF: %p\nnewlineCount: %d\ntotalLines: %d\nnewlineStart: %d\nlineStart: %d\nrow: %d\ncolumn: %d\nrowLength: %d\n-----\n", studioContext->fileIsOpen, studioContext->fileIsSaved, studioContext->pageDataStart, studioContext->rowDataStart, studioContext->fileName, studioContext->fileSize, studioContext->openEOF, studioContext->newlineCount, studioContext->totalLines, studioContext->newlineStart, studioContext->lineStart, studioContext->row, studioContext->column, studioContext->rowLength);
    }
}

static void menu_FileOpen(struct context_t *studioContext, struct preferences_t *studioPreferences, char *fileNames, unsigned int fileCount) {
    while (kb_AnyKey());

    unsigned int rowsPerScreen = (fileCount + 1) / 2;

    if (rowsPerScreen > 8) {
        rowsPerScreen = 8;
    }

    uint8_t boxY = 101 - rowsPerScreen * 17 / 2;
    uint8_t boxHeight =  19 + rowsPerScreen * 17;

    unsigned int fileStartLoc = 0; // It's CEaShell all over again
    unsigned int fileSelected = 0;

    asm_spi_BeginFrame();
    gfx_SetColor(OUTLINE);
    gfx_Rectangle_NoClip(84, boxY, 142, boxHeight);
    gfx_Rectangle_NoClip(85, boxY + 1, 140, boxHeight - 2);
    gfx_Rectangle_NoClip(214, boxY + 16, 2, boxHeight - 18);
    gfx_FillRectangle_NoClip(86, boxY + 2, 138, 14);
    fontlib_SetCursorPosition(122, boxY + 2);
    fontlib_DrawString("Open file");

    menu_FileOpenRedraw(fileNames, (fileCount + 1) / 2, fileCount, 0, 0, rowsPerScreen, boxY, boxHeight);

    asm_spi_EndFrame();

    bool keyPressed = false;
    clock_t clockOffset = clock();

    unsigned int bottomItem = fileCount + fileCount % 2;

    while (!kb_IsDown(kb_KeyClear) && !kb_IsDown(kb_Key2nd) && !kb_IsDown(kb_KeyEnter)) {
        kb_Scan();

        if (!kb_AnyKey()) {
            keyPressed = false;
            clockOffset = clock();
        }

        if (kb_Data[7] && (!keyPressed || clock() - clockOffset > CLOCKS_PER_SEC / 16) && fileCount) {
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

            if (kb_IsDown(kb_KeyLeft)  && fileCount > 1) {
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
            } else if (kb_IsDown(kb_KeyRight) && fileCount > 1) {
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

            asm_spi_BeginFrame();
            menu_FileOpenRedraw(fileNames, (fileCount + 1) / 2, fileCount, fileStartLoc, fileSelected, rowsPerScreen, boxY, boxHeight);
            asm_spi_EndFrame();

            util_WaitBeforeKeypress(&clockOffset, &keyPressed);
        }
    }

    if (kb_IsDown(kb_KeyClear) || !fileCount) {
        while (kb_AnyKey());
        return; // Return early
    }

    if (!util_OpenFile(studioContext, &fileNames[(fileStartLoc + fileSelected) * 9])) {
        gfx_ZeroScreen();
        ui_DrawUIMain(0, studioContext->totalLines, studioContext->lineStart);

        if (studioContext->fileIsOpen) {
            ui_UpdateText(studioContext, studioPreferences, UPDATE_ALL);
            ui_DrawCursor(studioContext->row, studioContext->column, true, false);
        } else {
            ui_NoFile();
        }

        ui_DrawMenuBox(0, 168, 73, 55, 1, 3, "New file", "Open file", "Save file");
        struct error_t error = {0, ERROR_NO_MEM};
        menu_Error(error);
    }

    //dbg_printf("-----\nfileIsOpen: %d\nfileIsSaved: %d\npageDataStart: %p\nrowDataStart: %p\nfileName: %s\nfileSize: %d\nopenEOF: %p\nnewlineCount: %d\ntotalLines: %d\nnewlineStart: %d\nlineStart: %d\nrow: %d\ncolumn: %d\nrowLength: %d\n-----\n", studioContext->fileIsOpen, studioContext->fileIsSaved, studioContext->pageDataStart, studioContext->rowDataStart, studioContext->fileName, studioContext->fileSize, studioContext->openEOF, studioContext->newlineCount, studioContext->totalLines, studioContext->newlineStart, studioContext->lineStart, studioContext->row, studioContext->column, studioContext->rowLength);
}

void menu_File(struct context_t *studioContext, struct preferences_t *studioPreferences) {
    asm_spi_BeginFrame();
    ui_DrawUIMain(1, studioContext->totalLines, studioContext->lineStart);
    asm_spi_EndFrame();

    while (kb_AnyKey()); // Wait for key to be released

    asm_spi_BeginFrame();
    ui_DrawUIMain(0, studioContext->totalLines, studioContext->lineStart);
    ui_DrawMenuBox(0, 168, 73, 55, 0, 3, "New file", "Open file", "Save file");
    asm_spi_EndFrame();

    uint8_t option = 0;

    bool keyPressed = false;
    clock_t clockOffset = clock();

    while (!kb_IsDown(kb_KeyClear) && !kb_IsDown(kb_KeyYequ) && !kb_IsDown(kb_Key2nd) && !kb_IsDown(kb_KeyEnter)) {
        kb_Scan();

        if (!kb_AnyKey()) {
            keyPressed = false;
            clockOffset = clock();
        }

        if (kb_Data[7] && (!keyPressed || clock() - clockOffset > CLOCKS_PER_SEC / 16)) {
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

            asm_spi_BeginFrame();
            ui_DrawMenuBox(0, 168, 73, 55, option, 3, "New file", "Open file", "Save file");
            asm_spi_EndFrame();

            util_WaitBeforeKeypress(&clockOffset, &keyPressed);
        }
    }

    if (kb_IsDown(kb_KeyYequ)) { // Ensure the menu doesn't get opened again immediately
        asm_spi_BeginFrame();
        ui_DrawUIMain(1, studioContext->totalLines, studioContext->lineStart);
        asm_spi_EndFrame();

        while (kb_AnyKey());
    } else if (kb_IsDown(kb_Key2nd) || kb_IsDown(kb_KeyEnter)) {
        switch (option) {
            case 0: // New file
                if (studioContext->fileIsSaved || menu_Warning(WARNING_UNSAVED)) {
                    edit_RedrawEditor(studioContext, studioPreferences);
                    menu_FileNew(studioContext);
                }

                break;
            case 1: { // Open file
                if (studioContext->fileIsSaved || menu_Warning(WARNING_UNSAVED)) {
                    edit_RedrawEditor(studioContext, studioPreferences);
                    unsigned int fileCount = 0;
                    util_GetFiles(&fileCount, SOURCE_HEADER);
                    menu_FileOpen(studioContext, studioPreferences, (char *)os_PixelShadow, fileCount);
                }

                break;
            }
            case 2: // Save file
                if (!(studioContext->fileIsOpen)) {
                    break;
                }

                studioContext->fileIsSaved = true;

                if (!asm_files_WriteFile(studioContext->fileName, studioContext->fileSize)) {
                    struct error_t error = {0, ERROR_NO_MEM};
                    menu_Error(error);
                }

                while (kb_AnyKey());

                // dbg_printf("fileIsOpen: %d\nfileIsSaved: %d\npageDataStart: %p\nrowDataStart: %p\nfileName: %s\nfileSize: %d\nopenEOF: %p\nnewlineCount: %d\ntotalLines: %d\nnewLineStart: %d\nlineStart: %d\nrow: %d\ncolumn: %d\nrowLength: %d\ninputMode: %d\n", studioContext->fileIsOpen, studioContext->fileIsSaved, studioContext->pageDataStart, studioContext->rowDataStart, studioContext->fileName, studioContext->fileSize, studioContext->openEOF, studioContext->newlineCount, studioContext->totalLines, studioContext->newlineStart, studioContext->lineStart, studioContext->row, studioContext->column, studioContext->rowLength, studioContext->inputMode);

                break;
            default:
                break;
        }
    }
}

void menu_Goto(struct context_t *studioContext) {
    asm_spi_BeginFrame();
    ui_DrawUIMain(3, studioContext->totalLines, studioContext->lineStart);
    asm_spi_EndFrame();

    while (kb_AnyKey()); // Wait for key to be released

    asm_spi_BeginFrame();
    ui_DrawUIMain(0, studioContext->totalLines, studioContext->lineStart);
    gfx_SetColor(OUTLINE);
    gfx_FillRectangle_NoClip(101, 207, 71, 16);
    gfx_Rectangle_NoClip(172, 207, 36, 18);
    gfx_Rectangle_NoClip(173, 208, 34, 16);

    gfx_SetColor(BACKGROUND);
    gfx_FillRectangle_NoClip(174, 209, 32, 14);

    fontlib_SetForegroundColor(TEXT_DEFAULT);
    fontlib_SetCursorPosition(104, 210);
    fontlib_DrawString("Goto Line:");
    asm_spi_EndFrame();

    char *input = util_StringInputBox(175, 210, 5, INPUT_NUMBERS, kb_KeyZoom);

    if (input != NULL) {
        int targetLine = asm_misc_StringToInt(input) - 1;

        if (targetLine >= 0 && (unsigned int)targetLine < studioContext->newlineCount) {
            studioContext->row = 0;
            studioContext->column = 0;

            while (studioContext->newlineStart != (unsigned int)targetLine) {
                if ((unsigned int)targetLine < studioContext->newlineStart) {
                    studioContext->newlineStart -= ((*(studioContext->pageDataStart - 1) == '\n') || !(studioContext->lineStart));
                    studioContext->lineStart--;
                    studioContext->pageDataStart = asm_files_PreviousLine(studioContext->pageDataStart, studioContext->openEOF);
                    studioContext->rowDataStart = studioContext->pageDataStart;
                    studioContext->rowLength = asm_files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
                } else if (studioContext->lineStart + 14 < studioContext->totalLines) {
                    studioContext->lineStart++;
                    studioContext->pageDataStart = asm_files_NextLine(studioContext->pageDataStart);
                    studioContext->rowDataStart = studioContext->pageDataStart;
                    studioContext->rowLength = asm_files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
                    studioContext->newlineStart += (*(studioContext->pageDataStart - 1) == '\n');
                } else {
                    for (unsigned int currentLine = studioContext->newlineStart; currentLine < (unsigned int)targetLine;) {
                        studioContext->row++;
                        studioContext->rowDataStart = asm_files_NextLine(studioContext->rowDataStart);
                        studioContext->rowLength = asm_files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
                        currentLine += (*(studioContext->rowDataStart - 1) == '\n');
                    }

                    break; // Ensure it doesn't get stuck in an infinite loop if line is right at the end
                }
            }
        }
    }

    if (!kb_IsDown(kb_KeyClear)) {
        if (kb_IsDown(kb_KeyZoom)) { // Ensure the menu doesn't get opened again immediately
            asm_spi_BeginFrame();
            ui_DrawUIMain(3, studioContext->totalLines, studioContext->lineStart);
            asm_spi_EndFrame();
        }

        while (kb_AnyKey());
    }
}

void menu_CharsRedraw(uint8_t selected, const char *chars) {
    gfx_SetColor(OUTLINE);
    gfx_FillRectangle_NoClip(165, 178, 117, 45);
    gfx_SetColor(BACKGROUND);
    gfx_FillRectangle_NoClip(167, 194, 113, 29);
    fontlib_SetCursorPosition(167, 180);
    fontlib_SetForegroundColor(TEXT_DEFAULT);
    fontlib_DrawString("Insert Character");
    gfx_SetColor(OUTLINE);

    unsigned int drawX = 168;
    uint8_t drawY = 195;

    for (uint8_t drawing = 0; drawing < 16; drawing++) {
        if (selected == drawing) {
            gfx_FillRectangle_NoClip(drawX, drawY, 13, 13);
        }

        fontlib_SetCursorPosition(drawX + 3, drawY);
        fontlib_DrawGlyph(chars[drawing]);

        if (drawing == 7) {
            drawX = 168;
            drawY = 209;
        } else {
            drawX += 14;
        }
    }
}

char menu_Chars(struct context_t *studioContext) {
    asm_spi_BeginFrame();
    ui_DrawUIMain(4, studioContext->totalLines, studioContext->lineStart);
    asm_spi_EndFrame();

    while (kb_AnyKey()); // Wait for key to be released

    bool keyPressed = false;
    uint8_t selected = 0;
    static const char chars[16] = {'\'', '`', ';', '@', '$', '~', '_', '!', '|', '<', '=', '>', '%', '\\', '#', '&'};

    asm_spi_BeginFrame();
    menu_CharsRedraw(0, chars);
    asm_spi_EndFrame();

    clock_t clockOffset = clock();

    while (!kb_IsDown(kb_KeyClear) && !kb_IsDown(kb_KeyTrace)) {
        kb_Scan();

        if (!kb_AnyKey()) {
            keyPressed = false;
            clockOffset = clock();
        }

        if (kb_Data[7] && (!keyPressed || clock() - clockOffset > CLOCKS_PER_SEC / 16)) {
            if (kb_IsDown(kb_KeyUp) || kb_IsDown(kb_KeyDown)) {
                if (selected > 7) {
                    selected -= 8;
                } else {
                    selected += 8;
                }
            }

            if (kb_IsDown(kb_KeyLeft)) {
                if (selected) {
                    selected--;
                } else {
                    selected = 15;
                }
            } else if (kb_IsDown(kb_KeyRight)) {
                if (selected < 15) {
                    selected++;
                } else {
                    selected = 0;
                }
            }

            asm_spi_BeginFrame();
            menu_CharsRedraw(selected, chars);
            asm_spi_EndFrame();

            util_WaitBeforeKeypress(&clockOffset, &keyPressed);
        } else if (kb_IsDown(kb_Key2nd) || kb_IsDown(kb_KeyEnter)) {
            while (kb_AnyKey());
            return chars[selected];
        }
    }

    if (!kb_IsDown(kb_KeyClear)) {
        if (kb_IsDown(kb_KeyTrace)) { // Ensure the menu doesn't get opened again immediately
            asm_spi_BeginFrame();
            ui_DrawUIMain(4, studioContext->totalLines, studioContext->lineStart);
            asm_spi_EndFrame();
        }

        while (kb_AnyKey());
    }

    return '\0';
}

static void menu_About(void) {
    asm_spi_BeginFrame();
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
    fontlib_DrawString("eZ80 Studio");
    fontlib_SetCursorPosition(87, 85);
    fontlib_DrawString("Version: "VERSION_NO);

    gfx_HorizLine_NoClip(87, 98, 136);

    fontlib_SetCursorPosition(87, 100);
    fontlib_DrawString("An eZ80 IDE for TI");
    fontlib_SetCursorPosition(87, 112);
    fontlib_DrawString("eZ80 calculators.");

    gfx_HorizLine_NoClip(87, 125, 136);

    fontlib_SetCursorPosition(87, 127);
    fontlib_DrawString("\xA9 2022 - 2024");
    fontlib_SetCursorPosition(87, 139);
    fontlib_DrawString("RoccoLox Programs,");
    fontlib_SetCursorPosition(87, 151);
    fontlib_DrawString("TIny_Hacker.");

    asm_spi_EndFrame();

    while (kb_AnyKey());

    while (!kb_AnyKey());
}

void menu_Settings(struct context_t *studioContext, struct preferences_t *studioPreferences) {
    asm_spi_BeginFrame();
    ui_DrawUIMain(5, studioContext->totalLines, studioContext->lineStart);
    asm_spi_EndFrame();

    while (kb_AnyKey()); // Wait for key to be released

    asm_spi_BeginFrame();
    ui_DrawUIMain(0, studioContext->totalLines, studioContext->lineStart);
    ui_DrawMenuBox(203, 168, 107, 55, 0, 3, "Themes       \xBB", "Highlighting \xBB", "About"); // \xBB is a right arrow icon
    asm_spi_EndFrame();

    uint8_t option = 0;

    bool keyPressed = false;
    clock_t clockOffset = clock();

    while (!kb_IsDown(kb_KeyClear) && !kb_IsDown(kb_KeyGraph)) {
        kb_Scan();

        if (!kb_AnyKey()) {
            keyPressed = false;
            clockOffset = clock();
        }

        if ((kb_Data[7] || kb_IsDown(kb_KeyEnter) || kb_IsDown(kb_Key2nd)) && (!keyPressed || clock() - clockOffset > CLOCKS_PER_SEC / 16)) {
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

                edit_RedrawEditor(studioContext, studioPreferences);
            }

            asm_spi_BeginFrame();
            ui_DrawMenuBox(203, 168, 107, 55, option, 3, "Themes       \xBB", "Highlighting \xBB", "About");
            asm_spi_EndFrame();

            util_WaitBeforeKeypress(&clockOffset, &keyPressed);
        }
    }

    if (kb_IsDown(kb_KeyGraph)) { // Ensure the menu doesn't get opened again immediately
        asm_spi_BeginFrame();
        ui_DrawUIMain(5, studioContext->totalLines, studioContext->lineStart);
        asm_spi_EndFrame();

        while (kb_AnyKey());
    }
}
