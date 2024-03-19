/**
 * --------------------------------------
 * 
 * eZ80 Studio Source Code - utility.h
 * By RoccoLox Programs and TIny_Hacker
 * Copyright 2022 - 2024
 * License: GPL-3.0
 * 
 * --------------------------------------
**/

#ifndef UTILITY_H
#define UTILITY_H

#include "defines.h"

#include <keypadc.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Read preferences from the AppVar, or set the default preferences if the AppVar doesn't exist.
 * 
 * @param studioPreferences eZ80 Studio preferences struct.
 */
void util_ReadPrefs(struct preferences_t *studioPreferences);

/**
 * @brief Write preferences to AppVar.
 * 
 * @param studioPreferences eZ80 Studio preferences struct.
 */
void util_WritePrefs(struct preferences_t *studioPreferences);

/**
 * @brief Gets a list of openable files.
 * 
 * @param fileCount Pointer to an int holding the number of openable files.
 * @return char* List of file names.
 */
char *util_GetFiles(unsigned int *fileCount);

/**
 * @brief Returns a pointer to the end of a token.
 * 
 * @param string String to search.
 * @param openEOF End of the currently opened file.
 * @return char* Pointer to the end of the token.
 */
char *util_GetStringEnd(char *string, char *openEOF);

/**
 * @brief Inserts a character at the current cursor location in the currently opened file.
 * 
 * @param character Character to insert.
 * @param studioContext eZ80 Studio context struct.
 * @return true Character inserted succesfully.
 * @return false Character was not inserted.
 */
bool util_InsertChar(char character, struct context_t *studioContext);

/**
 * @brief Displays a box asking for an input.
 * 
 * @param x X coordinate to begin drawing input box at.
 * @param y Y coordinate to begin drawing input box at.
 * @param stringLength Maximum length of input string.
 * @param inputMode Current input mode.
 * @param exitKey Key to press to exit the input box.
 * @return char* String typed into input box.
 */
char *util_StringInputBox(unsigned int x, uint8_t y, uint8_t stringLength, uint8_t inputMode, kb_lkey_t exitKey);

/**
 * @brief Waits before repeating a keypress.
 * 
 * @param clockOffset Clock offset for timer.
 * @param keyPressed Whether a key is currently pressed.
 */
void util_WaitBeforeKeypress(clock_t *clockOffset, bool *keyPressed);

#ifdef __cplusplus
}
#endif

#endif
