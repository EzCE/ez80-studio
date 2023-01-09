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

#ifdef __cplusplus
extern "C" {
#endif

struct preferences {
    bool theme;
};

struct context {
    bool fileIsOpen;                // is a file currently opened?
    char *pageDataStart;            // start of current page's data
    char *rowDataStart;             // start of current row's data
    char *fileName;                 // name of currently opened file
    char *openEOF;                  // pointer to end of file
    unsigned int newlineCount;      // number of newline characters
    unsigned int totalLines;        // number of total newlines (includes word-wrap)
    unsigned int lineStart;         // line to start drawing the page on
    unsigned int row;               // current row selected
    uint8_t rowLength;              //
    uint8_t column;                 // current column selected
};

// Read preferences from the appvar, or set the default preferences if the appvar doesn't exist
void util_ReadPrefs(struct preferences *studioPreferences);

// Write the preferences to the appvar
void util_WritePrefs(struct preferences *studioPreferences);

char *util_GetFiles(unsigned int *fileCount);

#ifdef __cplusplus
}
#endif

#endif
