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

#ifdef __cplusplus
extern "C" {
#endif

struct preferences {
    bool theme;
};

struct context {
    bool fileIsOpen;                // is a file currently opened?
    char *pageDataStart;            // start of current page's data
    char *fileName;                 // name of currently opened file
    unsigned int newlineCount;      // number of newline characters
    unsigned int totalLines;        // number of total newlines (includes word-wrap)
    unsigned int lineStart;         // line to start drawing the page on
    char *fileNames;                // names of all valid files
};

// Read preferences from the appvar, or set the default preferences if the appvar doesn't exist
void util_ReadPrefs(struct preferences *studioPreferences);

// Write the preferences to the appvar
void util_WritePrefs(struct preferences *studioPreferences);

char *util_GetFiles(char *fileNames, unsigned int *fileCount);

#ifdef __cplusplus
}
#endif

#endif
