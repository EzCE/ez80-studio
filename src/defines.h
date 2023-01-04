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

// Palette entries

#define BACKGROUND          0
#define OUTLINE             1
#define CURSOR              2
#define TEXT_DEFAULT        3
#define TEXT_LABEL          4
#define TEXT_INSTRUCTION    5
#define TEXT_REGISTER       6
#define TEXT_NUMBER         7
#define TEXT_PARENTHESIS    8
#define TEXT_COMMENT        9

// Preferences

#define LIGHT_THEME         true
#define DARK_THEME          false

#ifdef __cplusplus
}
#endif

#endif
