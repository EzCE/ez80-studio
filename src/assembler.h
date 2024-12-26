/**
 * --------------------------------------
 * 
 * eZ80 Studio Source Code - assembler.h
 * By RoccoLox Programs and TIny_Hacker
 * Copyright 2022 - 2024
 * License: GPL-3.0
 * 
 * --------------------------------------
**/

#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "defines.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Check if a string is a 1-byte char.
 * 
 * @param string String to evaluate
 * @return true String is a char.
 * @return false String is not a char.
 */
bool assembler_IsChar(char *string);

/**
 * @brief Assemble the currently open file.
 * 
 * @param studioContext eZ80 Studio context struct.
 * @return struct error_t Error returned by assembler.
 */
struct error_t assembler_Main(struct context_t *studioContext);

#ifdef __cplusplus
}
#endif

#endif
