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
    bool fileIsSaved;               // is the file saved?
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

/**
 * @brief Read preferences from the AppVar, or set the default preferences if the AppVar doesn't exist.
 * 
 * @param studioPreferences ez80 Studio context struct.
 */
void util_ReadPrefs(struct preferences_t *studioPreferences);

/**
 * @brief Write preferences to AppVar.
 * 
 * @param studioPreferences ez80 Studio context struct.
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
 * @brief Get a keypress.
 * 
 * @return uint8_t GetCSC code of pressed key.
 */
uint8_t util_GetSingleKeyPress(void);

/**
 * @brief Returns the character associated with a key press.
 * 
 * @param key Key code.
 * @param mode Current input mode.
 * @return char Character associated with key press.
 */
char util_KeyToChar(uint8_t key, uint8_t mode);

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

#ifdef __cplusplus
}
#endif

#endif
