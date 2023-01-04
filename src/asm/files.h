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

#ifdef __cplusplus
extern "C" {
#endif

bool files_CountLines(char *fileName, unsigned int *newlineCount);

#ifdef __cplusplus
}
#endif

#endif
