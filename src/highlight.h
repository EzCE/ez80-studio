/**
 * --------------------------------------
 * 
 * ez80 Studio Source Code - highlight.h
 * By RoccoLox Programs and TIny_Hacker
 * Copyright 2022 - 2023
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

#define NUMBER_HEX      0
#define NUMBER_DEC      1
#define NUMBER_OCT      2
#define NUMBER_BIN      3

uint8_t hlight_GetHighlightColor(char *string, char *stringEnd, bool highlighting);

#ifdef __cplusplus
}
#endif

#endif