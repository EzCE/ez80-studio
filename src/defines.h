/**
 * --------------------------------------
 * 
 * ez80 Studio Source Code - defines.h
 * By RoccoLox Programs and TIny_Hacker
 * Copyright 2022 - 2023
 * License: GPL-3.0
 * 
 * --------------------------------------
**/

#ifndef DEFINES_H
#define DEFINES_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// File header for valid source files: 0xEF7A (Also uncompiled assembly header for TI-BASIC programs)

#define SOURCE_HEADER       "\xEF\x7A"

// Palette entries (Also used for token types because why not, they're already here)

#define BACKGROUND          0
#define OUTLINE             1
#define CURSOR              2
#define TEXT_DEFAULT        3
#define TEXT_LABEL          4
#define TEXT_INSTRUCTION    5
#define TEXT_REGISTER       6
#define TEXT_NUMBER         7
#define TEXT_PARENTHESIS    8
#define TEXT_STRING         9
#define TEXT_COMMENT        10

// Preferences

#define LIGHT_THEME         true
#define DARK_THEME          false

// Input modes

#define INPUT_NUMBERS       0
#define INPUT_UPPERCASE     1
#define INPUT_LOWERCASE     2

#ifdef __cplusplus
}
#endif

#endif
