/**
 * --------------------------------------
 * 
 * eZ80 Studio Source Code - assembler.c
 * By RoccoLox Programs and TIny_Hacker
 * Copyright 2022 - 2024
 * License: GPL-3.0
 * 
 * --------------------------------------
**/

#include "assembler.h"
#include "highlight.h"
#include "utility.h"
#include "asm/misc.h"
#include "asm/spi.h"

#include <graphx.h>
#include <string.h>

static void assembler_SanitizeLine(char *line, char *string, char *endOfFile) {
    bool inQuotes = false;
    bool inInstruction = false;
    char *stringEnd;

    while (*string != '\n' && string <= endOfFile) {
        if (*string == '\'' || *string == '\"') {
            inQuotes = !inQuotes;

            if (!inQuotes) { // Just exited quotes
                *line = *string;
                string++;
                line++;
                continue;
            }
        }

        if (inQuotes) {
            *line = *string;
            string++;
            line++;
            continue;
        }

        if (*string == ' ') {
            string++;
            continue;
        } else if (*string == ';') {
            break;
        }

        stringEnd = util_GetStringEnd(string, endOfFile);

        if (hlight_Instruction(string, stringEnd)) {
            inInstruction = true;
            strcpy(line, hlight_GetTokenString(string, stringEnd));
            line += stringEnd - string;
            string = stringEnd;
            stringEnd = util_GetStringEnd(string, endOfFile);

            if (hlight_Modifier(string, stringEnd)) {
                strcpy(line, hlight_GetTokenString(string, stringEnd));
                line += stringEnd - string;
                string = stringEnd;
            }

            *line = ' '; // Separate arguments
            line++;
        } else if (hlight_Register(string, stringEnd) || hlight_Condition(string, stringEnd)) {
            strcpy(line, hlight_GetTokenString(string, stringEnd));
            line += stringEnd - string;
            string = stringEnd;
        } else if ((!strncmp(string, ":=", 2) || !strncasecmp(string, "equ", 3) || !strncasecmp(string, ".equ", 4)) && *(string - 1) == ' ') {
            if (*string == ':') { // This gets separated
                strcpy(line, ":=");
                line += 2;
                string += 2;
            } else {
                strcpy(line, hlight_GetTokenString(string, stringEnd));
                line += stringEnd - string;
                string = stringEnd;
            }

            *line = ' '; // Separate equates
            line++;
        } else if (inInstruction) {
            if (*string == ',' || *string == '(' || *string == ')') {
                *line = *string;
                line++;
            } else if (*(line - 1) != '#') {
                *line = '#';
                line++;
            }

            string = stringEnd;
        } else {
            *line = *string;
            string++;
            line++;
        }
    }

    if (*(line - 1) == ' ') {
        line--;
    }

    *line = '\0';
}

static bool assembler_IsLabel(char *line) {
    while (*line != '\0') {
        if (*line == ' ') {
            return false;
        } else if (*line == ':') {
            return true;
        }

        line++;
    }

    return false;
}

static bool assembler_IsEquate(char *line) {
    while (*line != ' ' && *line != '\0') {
        line++;
    }

    if (*line == ' ') {
        line++;
        return (!strncmp(line, ":=", 2) || !strncasecmp(line, "equ", 3) || !strncasecmp(line, ".equ", 4));
    }

    return false;
}

static unsigned int assembler_GetDataSize(char *data) {
    if (*data != 'd') {
        return 0;
    }

    data++;
    uint8_t perData = 0;

    switch (*data) {
        case 'b':
            perData = 1;
            break;
        case 'w':
            perData = 2;
            break;
        case 'l':
            perData = 3;
            break;
        case 'd':
            perData = 4;
            break;
        case 'q':
            perData = 8;
            break;
        default:
            return 0;
    }

    unsigned int size = 0;

    while (*data != '\0') {
        if (*data == '#') {
            size += perData;
        } else if (*data == '\"' || *data == '\'') {
            unsigned int tempSize = 0;
            data++;

            while (*data != '\"' && *data != '\'') {
                if (*data == '\0') {
                    return 0;
                }

                if (*data == '\\') {
                    data++;
                }

                tempSize++;
                data++;
            }

            if (tempSize % perData) {
                tempSize += perData - (tempSize % perData);
            }

            size += tempSize;
        }

        data++;
    }

    dbg_printf("\nSize: %u\n", size);

    return size;
}

uint8_t assembler_Main(struct context_t *studioContext) {
    asm_spi_BeginFrame(); // Stop display updates since we use the other buffer
    asm_misc_ClearBuffer(gfx_vram);

    char *string = (char *)EDIT_BUFFER;
    static char line[MAX_LINE_LENGTH_ASM];

    void *offset = (void *)os_userMem;
    void *symbolEntry = (void *)EDIT_BUFFER + MAX_FILE_SIZE + 128;
    dbg_printf("Symbol Table Start: %p\n", symbolEntry);

    while (string <= studioContext->openEOF) {
        assembler_SanitizeLine(line, string, studioContext->openEOF);

        while (*string != '\n' && string <= studioContext->openEOF) {
            string++;
        }

        string++;

        dbg_printf("%s |", line);

        if (assembler_IsLabel(line)) {
            dbg_printf("Label @ Offset %p | ", offset);
            strcpy(symbolEntry, line);
            symbolEntry += strlen(line) + 1;
            *(uint8_t *)symbolEntry = 3;
            symbolEntry++;
            *(void **)symbolEntry = offset;
            symbolEntry += 3;
        } else if (assembler_IsEquate(line)) {
            dbg_printf("Equate | ");
            // Add equate to symbol table
        } else if (assembler_GetDataSize(line)) {
            offset += assembler_GetDataSize(line);
        } else if (asm_misc_FindOpcode(line)) {
            struct opcode_t *opcode = asm_misc_FindOpcode(line);
            offset += opcode->size;
            dbg_printf("Size %u", opcode->size);

            if (opcode >= &asm_opcodes_AfterCB && opcode < &asm_opcodes_AfterDDCB) {
                offset++;
                dbg_printf(" (+ 1)");
            } else if (opcode >= &asm_opcodes_AfterDDCB) {
                offset += 3;
                dbg_printf(" (+ 3)");
            }

            dbg_printf(" | ");
            // Check table location to properly adjust for size
        } else if (*line != '\0') {
            return ERROR_INVAL_TOK;
        }

        dbg_printf("%s\n", line);
    }

    asm_spi_EndFrame();
    return ERROR_SUCCESS;
}
