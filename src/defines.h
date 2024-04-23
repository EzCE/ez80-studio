/**
 * --------------------------------------
 * 
 * eZ80 Studio Source Code - defines.h
 * By RoccoLox Programs and TIny_Hacker
 * Copyright 2022 - 2024
 * License: GPL-3.0
 * 
 * --------------------------------------
**/

#ifndef DEFINES_H
#define DEFINES_H

#include <stdbool.h>
#include <stdint.h>


#include <debug.h>


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief PixelShadow RAM location.
 * 
 */
#define os_PixelShadow      ((uint8_t *)0xD031F6)

/**
 * @brief userMem RAM location.
 * 
 */
#define os_userMem          ((uint8_t *)0xD031F6)

/**
 * Opcode Map - Second Opcode (after $CB)
 */
extern struct opcode_t asm_opcodes_AfterCB;

/**
 * Opcode Map - Second Opcode (after $DD)
 */
extern struct opcode_t asm_opcodes_AfterDD;

/**
 * Opcode Map - Second Opcode (after $ED)
 */
extern struct opcode_t asm_opcodes_AfterED;

/**
 * Opcode Map - Second Opcode (after $FD)
 */
extern struct opcode_t asm_opcodes_AfterFD;

/**
 * Opcode Map - Second Opcode (after $DDCB##)
 */
extern struct opcode_t asm_opcodes_AfterDDCB;

/**
 * Opcode Map - Second Opcode (after $FDCB##)
 */
extern struct opcode_t asm_opcodes_AfterFDCB;

/**
 * End of Opcode Map.
 */
extern struct opcode_t asm_opcodes_TableEnd;

/**
 * File header for valid source files: 0xEF7A (Also uncompiled assembly header for TI-BASIC programs).
*/
#define SOURCE_HEADER       "\xEF\x7A"

/**
 * Palette entries (Also used for token types when highlighting because why not, they're already here).
*/
#define BACKGROUND          0       /* Background color. */
#define OUTLINE             1       /* Outlines of dialog boxes, buttons, etc. */
#define CURSOR              2       /* Cursor color, also used for pressed buttons. */
#define TEXT_DEFAULT        3       /* Default text color. */
#define TEXT_LABEL          4       /* Text color for labels. */
#define TEXT_INSTRUCTION    5       /* Text color for instructions. */
#define TEXT_REGISTER       6       /* Text color for registers. */
#define TEXT_NUMBER         7       /* Text color for numbers. */
#define TEXT_PARENTHESIS    8       /* Text color for parenthesis. */
#define TEXT_STRING         9       /* Text color for strings. */
#define TEXT_COMMENT        10      /* Text color for comments. */

/**
 * Number types, used by the highlighting code.
*/
#define NUMBER_HEX      0           /* Hexadecimal number. */
#define NUMBER_DEC      1           /* Decimal number. */
#define NUMBER_OCT      2           /* Octal number. */
#define NUMBER_BIN      3           /* Binary number. */

/**
 * GUI color themes.
*/
#define LIGHT_THEME         true    /* Light GUI color theme. */
#define DARK_THEME          false   /* Dark GUI color theme. */

/**
 * Text input modes.
*/
#define INPUT_NUMBERS       0       /* Numbers / symbols keypad layout. */
#define INPUT_UPPERCASE     1       /* Uppercase letters keypad layout. */
#define INPUT_LOWERCASE     2       /* Lowercase letters keypad layout. */

/**
 * Maximum file size. 65500 bytes to be safe, does not include header.
*/
#define MAX_FILE_SIZE       65500

/**
 * Maximum symbol table size.
*/
#define MAX_SYMBOL_TABLE    11000

/**
 * Error codes used in the editor and assembler.
*/
#define ERROR_SUCCESS       0       /* The action was completed succesfully. */
#define ERROR_UNKNOWN       1       /* The action failed for an unknown reason. (Not sure if this will be used?) */
#define ERROR_NO_MEM        2       /* There is not enough memory to perform the requested action. */
#define ERROR_INVAL_TOK     3       /* A token was invalid. */

/**
 * Pointer to the start of editable data in the edit buffer. Note: Does not include file header. To include the file header, use EDIT_BUFFER - 2
*/
#define EDIT_BUFFER         (uint8_t *)0xD52C02

/**
 * Maximum number of bytes for a token. (Highlighting)
*/
#define MAX_TOK_LENGTH_HL   6

/**
 * Maximum number of bytes for a line. (Assembling)
*/
#define MAX_LINE_LENGTH_ASM 255

/**
 * Maximum length of input string for the util_StringInputBox function.
*/
#define MAX_INPUT_LENGTH     9

/**
 * Editor preferences struct, saved in the AppVar.
*/
struct preferences_t {
    bool theme;                     /* Color theme used by the editor. */
    bool highlighting;              /* Whether syntax highlighting is enabled. */
};

/**
 * Editor context struct.
*/
struct context_t {
    bool fileIsOpen;                /* Whether a file is currently open in the editor. */
    bool fileIsSaved;               /* Whether the currently open file has been modified since it was last saved. */
    char *pageDataStart;            /* Start of data for the current page of the open file being displayed. */
    char *rowDataStart;             /* Start of data for the currently selected row in the editor. */
    char fileName[9];               /* Name of currently opened file. */
    uint16_t fileSize;              /* Size of currently opened file (includes both data and header). */
    char *openEOF;                  /* Pointer to the end of the currently opened file's data in the edit buffer. Because it points to the last byte of data, it is equal to EDIT_BUFFER - 1 in an empty file. */
    unsigned int newlineCount;      /* Total number of newline characters in the currently opened file's data. */
    unsigned int totalLines;        /* Total number of lines, after calculating word-wrap. */
    unsigned int newlineStart;      /* First line of the page, before word-wrap (using newline characters). */
    unsigned int lineStart;         /* First line of the page, after calculating word-wrap. */
    unsigned int row;               /* Current row of the editor selected by the cursor (0 - 13). */
    uint8_t column;                 /* Current column of the editor selected by the cursor. */
    uint8_t rowLength;              /* Length of the currently selected row, in columns. */
};

struct opcode_t {
    uint8_t size;
    void *data;
};

#ifdef __cplusplus
}
#endif

#endif
