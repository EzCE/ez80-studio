/**
 * --------------------------------------
 * 
 * eZ80 Studio Source Code - highlight.h
 * By RoccoLox Programs and TIny_Hacker
 * Copyright 2022 - 2024
 * License: GPL-3.0
 * 
 * --------------------------------------
**/

#ifndef HIGHLIGHT_H
#define HIGHLIGHT_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Finds the color to highlight a specific token.
 * 
 * @param string Pointer to start of token.
 * @param stringEnd Pointer to end of token.
 * @param highlighting Whether highlighting is enabled.
 * @return uint8_t Highlight color.
 */
uint8_t hlight_GetHighlightColor(char *string, char *stringEnd, bool highlighting);

#ifdef __cplusplus
}
#endif

#endif