/**
 * --------------------------------------
 * 
 * ez80 Studio Source Code - utility.h
 * By RoccoLox Programs and TIny_Hacker
 * Copyright 2022 - 2023
 * License: GPL-3.0
 * 
 * --------------------------------------
**/

#ifndef UTILITY_H
#define UTILITY_H

#include <stdbool.h>
#include <stdint.h>
#include <keypadc.h>

#ifdef __cplusplus
extern "C" {
#endif

struct preferences_t {
    bool theme;
    bool highlighting;
};

struct context_t {
    bool fileIsOpen;                // is a file currently opened?
    char *fileDataStart;            // start of opened file's data
    char *pageDataStart;            // start of current page's data
    char *rowDataStart;             // start of current row's data
    char *fileName;                 // name of currently opened file
    uint16_t fileSize;              // size of the currently opened file
    char *openEOF;                  // pointer to end of file
    unsigned int newlineCount;      // number of newline characters
    unsigned int totalLines;        // number of total newlines (includes word-wrap)
    unsigned int lineStart;         // current line (includes newlines)
    unsigned int newlineStart;      // line to start drawing the page on
    unsigned int row;               // current row selected
    uint8_t column;                 // current column selected
    uint8_t rowLength;              // length of current row (in columns)
};

// Read preferences from the appvar, or set the default preferences if the appvar doesn't exist
void util_ReadPrefs(struct preferences_t *studioPreferences);

// Write the preferences to the appvar
void util_WritePrefs(struct preferences_t *studioPreferences);

char *util_GetFiles(unsigned int *fileCount);

char *util_GetStringEnd(char *string, char *openEOF);

char util_KeyToChar(uint8_t key, uint8_t mode);

char *util_StringInputBox(unsigned int x, uint8_t y, uint8_t stringLength, uint8_t inputMode, kb_lkey_t exitKey);

#ifdef __cplusplus
}
#endif

#endif
