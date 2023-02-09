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
