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

#include "utility.h"
#include "defines.h"
#include "asm/asm.h"

#include <fileioc.h>
#include <string.h>
#include <graphx.h>
#include <fontlibc.h>
#include <sys/timers.h>

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

char *util_GetFiles(unsigned int *fileCount) {
    uint8_t fileType = '\0';
    char *fileName;
    void *vatPtr = NULL;
    *fileCount = 0;
    unsigned int currentOffset = 0;

    asm_SortVAT();

    while ((fileName = ti_DetectAny(&vatPtr, SOURCE_HEADER, &fileType))) {
        if (fileType == OS_TYPE_APPVAR) {
            *fileCount = *fileCount + 1;
        }
    }

    vatPtr = NULL;
    char *fileNames = malloc(*fileCount * 9);

    while ((fileName = ti_DetectAny(&vatPtr, SOURCE_HEADER, &fileType))) {
        if (fileType == OS_TYPE_APPVAR) {
            strcpy(&fileNames[currentOffset], fileName); 
            currentOffset += 9;
        }
    }

    return fileNames;
}

char *util_GetStringEnd(char *string, char *openEOF) {
    bool singleChar = true;

    if (*string =='.') {
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
            *string == '/') {

            return string + singleChar;
        }

        singleChar = false;
        string++;
    }

    return string;
}

char *util_StringInputBox(unsigned int x, uint8_t y, uint8_t stringLength, uint8_t inputMode, kb_lkey_t exitKey) {
    bool keyPressed = false;
    bool cursorActive = true;
    uint8_t currentOffset = 0;
    uint8_t charCount = 0;

    timer_Enable(1, TIMER_32K, TIMER_NOINT, TIMER_UP);
    timer_Set(1, 0);

    char *input = malloc(stringLength);

    for (uint8_t i = 0; i <= stringLength; i++) {
        input[i] = '\0';
    }

    const char *charNums = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0""369\0\0\0\0\0""258\0\0\0\0""0147\0\0\0X\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
    const char *charUpper = "\0\0\0\0\0\0\0\0\0\0\0WRMH\0\0\0[VQLG\0\0\0ZUPKFC\0\0YTOJEBX\0XSNIDA\0\0\0\0\0\0\0\0";
    const char *charLower = "\0\0\0\0\0\0\0\0\0\0\0wrmh\0\0\0[vqlg\0\0\0zupkfc\0\0ytojeb\0\0xsnida\0\0\0\0\0\0\0\0";

    uint8_t key = 0;

    fontlib_SetForegroundColor(TEXT_DEFAULT);

    while (!kb_IsDown(kb_KeyClear) && !kb_IsDown(kb_Key2nd) && !kb_IsDown(kb_KeyEnter) && !kb_IsDown(exitKey)) {
        kb_Scan();

        if (!kb_AnyKey() && keyPressed) {
            keyPressed = false;
            timer_Set(1, 0);
        }

        if (kb_AnyKey() && (!keyPressed || timer_Get(1) > 3000)) {
            cursorActive = true;

            gfx_SetColor(BACKGROUND);
            gfx_FillRectangle_NoClip(x, y, charCount * 7 + 2, 12);

            if (kb_IsDown(kb_KeyClear) || kb_IsDown(exitKey)) {
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
            } else if (charCount < stringLength - 1) {
                if (!keyPressed) {
                    key = util_GetSingleKeyPress();
                }

                if (inputMode == INPUT_LOWERCASE) {
                    if (charLower[key]) {
                        for (uint8_t i = stringLength - 1; i != currentOffset; i--) {
                            input[i] = input[i - 1];
                        }

                        input[currentOffset] = charLower[key];
                        charCount++;
                        currentOffset++;
                    }
                } else if (inputMode == INPUT_UPPERCASE) {
                    if (charUpper[key]) {
                        for (uint8_t i = stringLength - 1; i != currentOffset; i--) {
                            input[i] = input[i - 1];
                        }

                        input[currentOffset] = charUpper[key];
                        charCount++;
                        currentOffset++;
                    }
                } else {
                    if (charNums[key]) {
                        for (uint8_t i = stringLength - 1; i != currentOffset; i--) {
                            input[i] = input[i - 1];
                        }

                        input[currentOffset] = charNums[key];
                        charCount++;
                        currentOffset++;
                    }
                }
            }

            gfx_SetColor(CURSOR);

            gfx_FillRectangle_NoClip(x + (currentOffset * 7), y, 2, 12); // Draw new cursor

            fontlib_SetCursorPosition(x + 1, y);
            fontlib_DrawString(input);

            gfx_BlitBuffer();

            if (!keyPressed) {
                while (timer_Get(1) < 9000 && kb_AnyKey());
            }

            keyPressed = true;
            timer_Set(1, 0);
        }

        if (timer_Get(1) > 10000 && !keyPressed) {
            if (cursorActive) {
                gfx_SetColor(CURSOR);
            } else {
                gfx_SetColor(BACKGROUND);
            }

            gfx_FillRectangle_NoClip(x + (currentOffset * 7), y, 2, 12);

            cursorActive = !cursorActive;
            timer_Set(1, 0);

            gfx_BlitBuffer();
        }
    }

    if (kb_IsDown(kb_Key2nd) || kb_IsDown(kb_KeyEnter)) {
        return input;
    }

    if (kb_IsDown(kb_KeyClear)) {
        while (kb_AnyKey());
    }

    free(input);
    return NULL;
}

// code by jacobly from here:
// https://ce-programming.github.io/toolchain/libraries/keypadc.html#getting-getcsc-codes-with-keypadc
uint8_t util_GetSingleKeyPress(void) {
    uint8_t only_key = 0;
    kb_Scan();

    for (uint8_t key = 1, group = 7; group; --group) {
        for (uint8_t mask = 1; mask; mask <<= 1, ++key) {
            if (kb_Data[group] & mask) {
                if (only_key) {
                    return false;
                } else {
                    only_key = key;
                }
            }
        }
    }

    return only_key;
}
