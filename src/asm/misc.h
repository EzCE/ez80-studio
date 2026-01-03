/**
 * --------------------------------------
 * 
 * eZ80 Studio Source Code - misc.h
 * By RoccoLox Programs and TIny_Hacker
 * Copyright 2022 - 2026
 * License: GPL-3.0
 * 
 * --------------------------------------
**/

#ifndef MISC_H
#define MISC_H

#include "defines.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Checks if a string matches an opcode.
 * 
 * @param string String to compare.
 * @return struct opcode_t* Pointer to location in opcode table if matched, or NULL if not.
 */
struct opcode_t *asm_misc_FindOpcode(char *string);

/**
 * @brief Converts a string such as "123" to an integer value.
 * 
 * @param string String to convert.
 * @return int Result of conversion, or -1 if the string was invalid.
 */
int asm_misc_StringToInt(char *string);

/**
 * @brief Clears an 8bpp VRAM buffer.
 * 
 * @param buffer Pointer to start of buffer.
 */
void asm_misc_ClearBuffer(void *buffer);

/**
 * @brief Sorts the VAT alphabetically.
 * 
 */
void asm_misc_SortVAT(void);

/**
 * @brief Scans the keypad and returns a character based on the key pressed.
 * 
 * @param inputMode Input mode, like 2nd mode, uppercase mode, or lowercase mode.
 * @return char Character found from keypress.
 */
char asm_misc_GetCharFromKey(uint8_t inputMode);

/**
 * @brief Copy backwards (lddr) from src -> dest, for a specified number of bytes.
 * 
 * @param src Pointer to first byte of data source.
 * @param dest Pointer to first byte of data destination.
 * @param bytes Bytes to copy.
 */
void asm_misc_ReverseCopy(void *src, void *dest, unsigned int bytes);

/**
 * @brief Retrieve a value for a specified symbol from the symbol table.
 * 
 * @param search Symbol to search for.
 * @param table Pointer to start of symbol table.
 */
void *asm_misc_FindSymbol(char *search, char *table);

#ifdef __cplusplus
}
#endif

#endif
