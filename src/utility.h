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
    char fileName[9];               // name of currently opened file
    unsigned int newlineCount;      // number of newline characters
    unsigned int totalLines;        // number of total newlines (includes word-wrap)
    unsigned int lineStart;         // line to start drawing the page on
};

// Read preferences from the appvar, or set the default preferences if the appvar doesn't exist
void util_ReadPrefs(struct preferences *studioPreferences);

// Write the preferences to the appvar
void util_WritePrefs(struct preferences *studioPreferences);

#ifdef __cplusplus
}
#endif

#endif
