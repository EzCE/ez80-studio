/**
 * --------------------------------------
 * 
 * eZ80 Studio Source Code - spi.h
 * By RoccoLox Programs and TIny_Hacker
 * Copyright 2022 - 2025
 * License: GPL-3.0
 * 
 * --------------------------------------
**/

#ifndef SPI_H
#define SPI_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Marks the beginning of a logical frame.
 * 
 */
void asm_spi_BeginFrame(void);

/**
 * @brief Marks the end of a logical frame.
 * 
 */
void asm_spi_EndFrame(void);

/**
 * @brief Necessary for Python models.
 * 
 */
void asm_spi_SetupSPI(void);

#ifdef __cplusplus
}
#endif

#endif
