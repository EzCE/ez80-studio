/**
 * --------------------------------------
 * 
 * ez80 Studio Source Code - files.h
 * By RoccoLox Programs and TIny_Hacker
 * Copyright 2022 - 2023
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

char *files_ReadFile(char *fileName);

bool files_CheckFileExists(char *fileName);

void files_CountLines(char *data, unsigned int *newlineCount, unsigned int *lineCount, char *openEOF);

uint8_t files_GetLineLength(char *rowDataStart, char *openEOF);

char *files_NextLine(char *currentLine);

char *files_PreviousLine(char *currentLine, char *fileDataStart, char *openEOF);

void files_InsertChar(char character, char *openEOF, unsigned int copySize);

void files_DeleteChar(char *delete, unsigned int copySize);

#ifdef __cplusplus
}
#endif

#endif
