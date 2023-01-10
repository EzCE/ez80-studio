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

bool files_CountLines(char *fileName, unsigned int *newlineCount, unsigned int *lineCount);

char *files_GetEOF(char *fileName);

uint8_t files_GetLineLength(char *rowDataStart, char *openEOF);

char *files_NextLine(char *currentLine);

char *files_PreviousLine(char *currentLine, char *fileDataStart);

#ifdef __cplusplus
}
#endif

#endif
