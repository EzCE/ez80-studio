/**
 * --------------------------------------
 * 
 * eZ80 Studio Source Code - lexer.h
 * By RoccoLox Programs and TIny_Hacker
 * Copyright 2022 - 2026
 * License: GPL-3.0
 * 
 * --------------------------------------
**/

#ifndef LEXER_H
#define LEXER_H

#include "defines.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Gets the type of a specified token.
 * 
 * @param tokStart Pointer to start of token.
 * @param tokEnd Pointer to end of token (start of next token).
 * @return uint8_t Token type, or 0 if not found.
 */
uint8_t asm_lexer_TokType(char *tokStart, char *tokEnd);

#ifdef __cplusplus
}
#endif

#endif