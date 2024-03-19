/**
 * --------------------------------------
 * 
 * eZ80 Studio Source Code - misc.h
 * By RoccoLox Programs and TIny_Hacker
 * Copyright 2022 - 2024
 * License: GPL-3.0
 * 
 * --------------------------------------
**/

#ifndef MISC_H
#define MISC_H

#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
}
#endif

#endif
