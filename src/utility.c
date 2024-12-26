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

#include "utility.h"
#include "defines.h"
#include "asm/misc.h"
#include "asm/files.h"
#include "asm/spi.h"

#include <fileioc.h>
#include <string.h>
#include <graphx.h>
#include <fontlibc.h>

static void util_SetDefaults(struct preferences_t *studioPreferences) {
    studioPreferences->theme = LIGHT_THEME;
    studioPreferences->highlighting = true;
}

void util_ReadPrefs(struct preferences_t *studioPreferences) {
    uint8_t appvar = ti_Open("EzStudio", "r");

    if (appvar) {
        ti_Read(studioPreferences, sizeof(struct preferences_t), 1, appvar);
    } else {
        util_SetDefaults(studioPreferences);
    }

    ti_Close(appvar);
}

void util_WritePrefs(struct preferences_t *studioPreferences) {
    uint8_t appvar = ti_Open("EzStudio", "w");

    ti_Write(studioPreferences, sizeof(struct preferences_t), 1, appvar);
    ti_SetArchiveStatus(true, appvar);
}

void util_GetFiles(unsigned int *fileCount, char *header) {
    uint8_t fileType = '\0';
    char *fileName;
    void *vatPtr = NULL;
    *fileCount = 0;
    unsigned int currentOffset = 0;

    asm_misc_SortVAT();

    while ((fileName = ti_DetectAny(&vatPtr, header, &fileType))) {
        if (fileType == OS_TYPE_APPVAR) {
            strcpy(&((char *)os_PixelShadow)[currentOffset], fileName);
            currentOffset += 9;
            *fileCount = *fileCount + 1;
        }
    }

}

char *util_GetStringEnd(char *string, char *openEOF) {
    bool singleChar = true;

    if (*string == '.') {
        string++;
    }

    while (string <= openEOF) {
        if (*string == ' ' ||
            *string == '\n' ||
            *string == ';' ||
            *string == '(' ||
            *string == ')' ||
            *string == '.' ||
            *string == ',' ||
            *string == '=' ||
            *string == '+' ||
            *string == '-' ||
            *string == '*' ||
            *string == '/' ||
            *string == '<' ||
            *string == '>' ||
            *string == '&' ||
            *string == '^' ||
            *string == '|') {

            return string + singleChar;
        }

        singleChar = false;
        string++;
    }

    return string;
}

char *util_GetStringStart(char *string) {
    bool singleChar = true;

    while (string >= (char *)EDIT_BUFFER) {
        if (*string == ' ' ||
            *string == '\n' ||
            *string == ';' ||
            *string == '(' ||
            *string == ')' ||
            *string == '.' ||
            *string == ',' ||
            *string == '=' ||
            *string == '+' ||
            *string == '-' ||
            *string == '*' ||
            *string == '/' ||
            *string == '<' ||
            *string == '>' ||
            *string == '&' ||
            *string == '^' ||
            *string == '|') {

            return string + !singleChar;
        }

        singleChar = false;
        string--;
    }

    return string + !singleChar;
}

bool util_InsertChar(char character, struct context_t *studioContext) {
    if (character) {
        if (studioContext->fileIsSaved) {
            studioContext->fileIsSaved = false;
        }

        asm_files_InsertChar(character, studioContext->openEOF, studioContext->openEOF - (studioContext->rowDataStart + studioContext->column) + 1);

        studioContext->fileSize++;
        studioContext->openEOF++;

        asm_files_CountLines(&(studioContext->newlineCount), &(studioContext->totalLines), studioContext->openEOF);
        studioContext->rowLength = asm_files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);

        if (character == '\n') {
            studioContext->column = 0;

            if (studioContext->row < 13 && studioContext->lineStart + studioContext->row + 1 != studioContext->totalLines) {
                studioContext->row++;
                studioContext->rowDataStart = asm_files_NextLine(studioContext->rowDataStart);
                studioContext->rowLength = asm_files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
            } else {
                studioContext->lineStart++;
                studioContext->pageDataStart = asm_files_NextLine(studioContext->pageDataStart);
                studioContext->rowDataStart = asm_files_NextLine(studioContext->rowDataStart);
                studioContext->rowLength = asm_files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
                studioContext->newlineStart += (*(studioContext->pageDataStart - 1) == '\n');
            }
        } else {
            if (studioContext->column < studioContext->rowLength) {
                studioContext->column++;
            } else {
                if (studioContext->row < 13 && studioContext->lineStart + studioContext->row + 1 != studioContext->totalLines) {
                    studioContext->row++;
                    studioContext->rowDataStart = asm_files_NextLine(studioContext->rowDataStart);
                    studioContext->rowLength = asm_files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
                    studioContext->column = 1; // Skip the new character
                } else if (studioContext->lineStart + 14 < studioContext->totalLines) {
                    studioContext->lineStart++;
                    studioContext->pageDataStart = asm_files_NextLine(studioContext->pageDataStart);
                    studioContext->rowDataStart = asm_files_NextLine(studioContext->rowDataStart);
                    studioContext->rowLength = asm_files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);
                    studioContext->column = 1;
                    studioContext->newlineStart += (*(studioContext->pageDataStart - 1) == '\n');
                }
            }
        }
    }


    return character != '\0';
}

char *util_StringInputBox(unsigned int x, uint8_t y, uint8_t stringLength, uint8_t inputMode, kb_lkey_t exitKey) {
    bool keyPressed = false;
    bool cursorActive = true;
    uint8_t currentOffset = 0;
    uint8_t charCount = 0;

    clock_t clockOffset = clock();

    static char input[MAX_INPUT_LENGTH];
    char character = '\0';

    for (uint8_t i = 0; i <= stringLength; i++) {
        input[i] = '\0';
    }

    fontlib_SetForegroundColor(TEXT_DEFAULT);

    while (!kb_IsDown(kb_KeyClear) && !kb_IsDown(exitKey)) {
        kb_Scan();

        if (!kb_AnyKey() && keyPressed) {
            keyPressed = false;
            clockOffset = clock();
        }

        if (kb_AnyKey() && (!keyPressed || clock() - clockOffset > CLOCKS_PER_SEC / 16)) {
            clockOffset = clock();
            cursorActive = true;

            gfx_SetColor(BACKGROUND);
            gfx_FillRectangle_NoClip(x, y, charCount * 7 + 2, 12);

            if (kb_IsDown(kb_KeyClear) || kb_IsDown(exitKey)) {
                break;
            } else if ((kb_IsDown(kb_Key2nd) || kb_IsDown(kb_KeyEnter)) && charCount != 0) {
                break;
            } else if (kb_IsDown(kb_KeyLeft)) {
                if (currentOffset) {
                    currentOffset--;
                }
            } else if (kb_IsDown(kb_KeyRight)) {
                if (currentOffset < charCount) {
                    currentOffset++;
                }
            } else if (kb_IsDown(kb_KeyUp)) {
                currentOffset = 0;
            } else if (kb_IsDown(kb_KeyDown)) {
                currentOffset = charCount;
            } else if (kb_IsDown(kb_KeyMode)) { // Backspace
                if (currentOffset && charCount) {
                    for (uint8_t i = currentOffset; input[i - 1] != '\0'; i++) {
                        input[i - 1] = input[i];
                    }

                    charCount--;
                    currentOffset--;
                }
            } else if (kb_IsDown(kb_KeyDel)) {
                if (currentOffset < charCount && charCount) {
                    for (uint8_t i = currentOffset; input[i] != '\0'; i++) {
                        input[i] = input[i + 1];
                    }

                    charCount--;
                }
            } else if (kb_IsDown(kb_KeyAlpha)) {
                if (inputMode == INPUT_LOWERCASE) {
                    inputMode = 0;
                } else {
                    inputMode++;
                }

                while (kb_AnyKey());
            } else if (charCount < stringLength - 1) {
                if (!keyPressed) {
                    character = asm_misc_GetCharFromKey(inputMode);
                }

                if ((character >= 'A' && character <= 'Z') || (character >= 'a' && character <= 'z') || (character >= '0' && character <= '9')) {
                    for (uint8_t i = stringLength - 1; i != currentOffset; i--) {
                        input[i] = input[i - 1];
                    }

                    input[currentOffset] = character;
                    charCount++;
                    currentOffset++;
                }
            }

            asm_spi_BeginFrame();
            gfx_SetColor(CURSOR);
            gfx_FillRectangle_NoClip(x + (currentOffset * 7), y, 2, 12); // Draw new cursor
            fontlib_SetCursorPosition(x + 1, y);
            fontlib_DrawString(input);
            asm_spi_EndFrame();

            util_WaitBeforeKeypress(&clockOffset, &keyPressed);
        }

        if (!keyPressed && clock() - clockOffset > CLOCKS_PER_SEC / 3) {
            if (cursorActive) {
                gfx_SetColor(CURSOR);
            } else {
                gfx_SetColor(BACKGROUND);
            }

            gfx_FillRectangle_NoClip(x + (currentOffset * 7), y, 2, 12);

            cursorActive = !cursorActive;
            clockOffset = clock();

            asm_spi_EndFrame();
        }
    }

    if (kb_IsDown(kb_Key2nd) || kb_IsDown(kb_KeyEnter)) {
        return input;
    }

    if (kb_IsDown(kb_KeyClear)) {
        while (kb_AnyKey());
    }

    return NULL;
}

void util_WaitBeforeKeypress(clock_t *clockOffset, bool *keyPressed) {
    if (!(*keyPressed)) {
        while ((clock() - *clockOffset < CLOCKS_PER_SEC / 3) && kb_AnyKey()) {
            kb_Scan();
        }
    }

    *keyPressed = true;
    *clockOffset = clock();
}

bool util_OpenFile(struct context_t *studioContext, char *fileName) {
    if (asm_files_ReadFile(fileName)) {
        strcpy(studioContext->fileName, fileName);
        studioContext->fileIsOpen = true;
        studioContext->fileIsSaved = true;

        uint8_t file = ti_Open(studioContext->fileName, "r");
        studioContext->fileSize = ti_GetSize(file);
        ti_Close(file);

        studioContext->pageDataStart = (char *)EDIT_BUFFER;
        studioContext->rowDataStart = studioContext->pageDataStart;
        studioContext->openEOF = (char *)EDIT_BUFFER + studioContext->fileSize - 3;

        studioContext->lineStart = 0;
        studioContext->newlineStart = 0;
        studioContext->row = 0;
        studioContext->column = 0;

        studioContext->rowLength = asm_files_GetLineLength(studioContext->rowDataStart, studioContext->openEOF);

        asm_files_CountLines(&(studioContext->newlineCount), &(studioContext->totalLines), studioContext->openEOF);

        return true;
    }

    return false;
}
