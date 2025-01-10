/**
 * --------------------------------------
 * 
 * eZ80 Studio Source Code - files.h
 * By RoccoLox Programs and TIny_Hacker
 * Copyright 2022 - 2025
 * License: GPL-3.0
 * 
 * --------------------------------------
**/

#ifndef FILES_H
#define FILES_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Reads the data (including header) of a specified file into EDIT_BUFFER - 2.
 * 
 * @param fileName File to read.
 * @return true Reading the file was successful.
 * @return false Reading the file was unsuccessful (the file didn't exist).
 */
bool asm_files_ReadFile(char *fileName);

/**
 * @brief Writes the current data of the edit buffer into a specified file.
 * 
 * @param fileName Name of the file to save to.
 * @param fileSize Total size of the data, including file header.
 * @return true Writing to the file was successful.
 * @return false Writing to the file was unsuccessful.
 */
bool asm_files_WriteFile(char *fileName, unsigned int fileSize);

/**
 * @brief Check if a file with the specified name exists.
 * 
 * @param name Name to check.
 * @param type File type.
 * @return true The file exists.
 * @return false The file doesn't exist.
 */
bool asm_files_CheckFileExists(char *name, uint8_t type);

/**
 * @brief Counts the number of newlines and word-wrapped lines in the currently opened file.
 * 
 * @param newlineCount Pointer to store newline count to.
 * @param lineCount Pointer to store word-wrapped line count to.
 * @param openEOF Pointer to the last byte of data in the edit buffer.
 */
void asm_files_CountLines(unsigned int *newlineCount, unsigned int *lineCount, char *openEOF);

/**
 * @brief Get the number of characters in a word-wrapped line beginning at a specified pointer.
 * 
 * @param rowDataStart Pointer to beginning of line.
 * @param openEOF Pointer to the last byte of data in the edit buffer.
 * @return uint8_t Number of characters (maximum 38 because more would wrap to the next line).
 */
uint8_t asm_files_GetLineLength(char *rowDataStart, char *openEOF);

/**
 * @brief Gets a pointer to the beginning of the next word-wrapped line.
 * 
 * @param currentLine Pointer to the beginning byte of the current line.
 * @return char* Pointer to the beginning of the next line.
 */
char *asm_files_NextLine(char *currentLine);

/**
 * @brief Gets a pointer to the beginning of the previous word-wrapped line.
 * 
 * @param currentLine Pointer to the beginning byte of the current line.
 * @param openEOF Pointer to the last byte of data in the edit buffer.
 * @return char* Pointer to the beginning of the previous line.
 */
char *asm_files_PreviousLine(char *currentLine, char *openEOF);

/**
 * @brief Inserts a character into the edit buffer, and shifts the data after it one byte over to make room.
 * 
 * @param character Character to insert.
 * @param openEOF Pointer to the last byte of data in the edit buffer.
 * @param copySize Number of bytes to copy after the character being inserted.
 */
void asm_files_InsertChar(char character, char *openEOF, unsigned int copySize);

/**
 * @brief Deletes a character in the edit buffer, and shifts the data after it one byte over to replace it.
 * 
 * @param delete Pointer to character to delete.
 * @param copySize Number of bytes to copy after the character being deleted.
 */
void asm_files_DeleteChar(char *delete, unsigned int copySize);

/**
 * @brief Creates a protected program containing the data at ti.vRam.
 * 
 * @param size Size of the program / data, including assembly header.
 * @param name Name of the program to create.
 * @return uint8_t Error code.
 */
uint8_t asm_files_CreateProg(uint16_t size, char *name);

#ifdef __cplusplus
}
#endif

#endif
