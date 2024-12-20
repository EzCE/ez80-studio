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
#include "lexer.h"
#include "parser.h"
#include "utility.h"
#include "asm/files.h"
#include "asm/misc.h"
#include "asm/spi.h"

#include <graphx.h>
#include <string.h>

static void assembler_SanitizeLine(char *line, char *string, char *endOfFile, bool pass2) {
    bool inQuotes = false;
    uint8_t nestParens = 0;
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

        uint8_t lexerType = asm_lexer_TokType(string, stringEnd);

        if (lexerType == TEXT_INSTRUCTION) {
            inInstruction = true;
            strcpy(line, hlight_GetTokenString(string, stringEnd));
            line += stringEnd - string;
            string = stringEnd;
            stringEnd = util_GetStringEnd(string, endOfFile);

            *line = ' '; // Separate arguments
            line++;
        } else if (lexerType == TEXT_REGISTER) {
            strcpy(line, hlight_GetTokenString(string, stringEnd));
            line += stringEnd - string;
            string = stringEnd;
        } else if (inInstruction && lexerType == TEXT_MODIFIER) {
            if (pass2) {
                strcpy(line, hlight_GetTokenString(string, stringEnd));
                line += 4;
            }

            string = stringEnd;
        } else if ((!strncmp(string, ":=", 2) || !strncasecmp(string, "equ", 3) || !strncasecmp(string, ".equ", 4)) && *(string - 1) == ' ') {
            *line = ' '; // Separate equates
            line++;

            if (*string == ':') { // This gets separated when tokenized
                strcpy(line, ":=");
                line += 2;
                string += 2;
            } else {
                strcpy(line, hlight_GetTokenString(string, stringEnd));
                line += stringEnd - string;
                string = stringEnd;
            }

            *line = ' ';
            line++;
        } else if (inInstruction) {
            if (*string == ',' || *string == '(' || *string == ')') {
                if (*string == ')') {
                    nestParens--;
                }

                if (!nestParens || pass2) {
                    *line = *string;
                    line++;
                } else if (*(line - 1) != '#') {
                    *line = '#';
                    line++;
                }

                if (*string == '(') {
                    nestParens++;
                }
            } else if (pass2) {
                strncpy(line, string, stringEnd - string);
                line += stringEnd - string;
                string = stringEnd;
            } else if (*(line - 1) != '#') {
                *line = '#';
                line++;
            }

            string = stringEnd;
        } else {
            strncpy(line, string, stringEnd - string);
            line += stringEnd - string;
            string = stringEnd;
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
        default:
            return 0;
    }

    unsigned int size = 0;
    data += 2;

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

uint8_t assembler_WriteData(char *output, char *line) {
    uint8_t error = ERROR_SUCCESS;
    line++;
    uint8_t perData = 0;

    switch (*line) {
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
    }

    line++;
    static char data[MAX_LINE_LENGTH_ASM - 3];

    while (*line != '\0') {
        line++;
        uint8_t i = 0;

        if (*line == '\"' || *line == '\'') {
            line++;

            while (*line != '\"' && *line != '\'') {
                if (*line == '\\') {
                    line++;
                }

                *(output++) = *(line++);
            }

            line++;
        } else {
            while (*line != '\0' && *line != ',') {
                data[i++] = *(line++);
            }

            data[i] = '\0';

            unsigned long result = parser_Eval(data, &error);

            switch (perData) {
                case 1:
                    *(uint8_t *)output = (uint8_t)result;
                    break;
                case 2:
                    *(uint16_t *)output = (uint16_t)result;
                    break;
                case 3:
                    *(unsigned int *)output = (unsigned int)result;
                    break;
                case 4:
                    *(unsigned long *)output = (unsigned long)result;
                    break;
            }

            output += perData;
        }
    }

    dbg_printf("%p\n", output);

    return error;
}

static uint8_t assembler_PutArgs(char *output, char *line, struct opcode_t *opcode) {
    bool relative = false;

    if (strncmp(line, "djnz", 4) || (*line == 'j' && *(line + 1) == 'r')) {
        relative = true;
    }

    while (*line != ' ' && *line != '\0') {
        line++;
    }

    if (*line == '\0') {
        return ERROR_SUCCESS;
    }

    line++;
    char *tokEnd = NULL;
    char *endOfLine = line + strlen(line) - 1;
    static char data[MAX_LINE_LENGTH_ASM - 4];
    memset(data, 0, MAX_LINE_LENGTH_ASM - 4);
    uint8_t error = ERROR_SUCCESS;
    uint8_t nestParens = 0;
    uint8_t dataOffset = 0;

    while (line <= endOfLine + 1) {
        tokEnd = util_GetStringEnd(line, endOfLine);

        if (asm_lexer_TokType(line, tokEnd) == TEXT_REGISTER) {
            line = tokEnd;
        } else if (*line == '(') {
            if (nestParens) {
                data[dataOffset++] = *line;
            }

            nestParens++;
            line++;
        } else if (*line == '+' && !dataOffset) {
            line++;
        } else if (*line == '\0' || *line == ')' || *line == ',') {
            if (nestParens && *line == ')') {
                nestParens--;

                if (nestParens) {
                    data[dataOffset++] = *line;
                }
            }

            if (!nestParens && dataOffset) {
                unsigned long arg = parser_Eval(data, &error);

                if (opcode->size == 4) {
                    *(unsigned int *)(output + 1) = (unsigned int)arg;
                    return error;
                } else if (opcode->size == 3) {
                    *(uint8_t *)(output + 1) = (uint8_t)arg;
                    output++;
                } else if (opcode->size == 2) {
                    if (relative) {
                        arg = ((uint8_t *)arg - (os_userMem + ((uint8_t *)output - OUTPUT)));

                        if ((int)arg < -128 || (int)arg > 127) {
                            error = ERROR_INVAL_EXPR;
                        }

                        *(int8_t *)(output + 1) = (int8_t)arg;
                        dbg_printf("\nRelative: %d\n",  *(int8_t *)(output + 1));
                    } else {
                        *(uint8_t *)(output + 1) = (uint8_t)arg;
                    }

                    return error;
                }
            }

            line++;
        } else {
            strncpy(data + dataOffset, line, tokEnd - line);
            dataOffset += tokEnd - line;
            line = tokEnd;
        }
    }

    return error;
}

unsigned long assembler_ReserveBytes(char *line, char *string, char *endOfFile, uint8_t *error) {
    if (*line != 'r') {
        return 0;
    }

    uint8_t perData = 0;

    switch (*(line + 1)) {
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
        default:
            return 0;
    }

    if (strncmp(" #", line + 2, 3)) {
        return 0;
    }

    memset(line, 0, MAX_LINE_LENGTH_ASM);

    assembler_SanitizeLine(line, string, endOfFile, true);

    return perData * parser_Eval(line + 3, error);
}

uint8_t assembler_GetSuffix(char *line, char *string, char *endOfFile, uint8_t *error) {
    assembler_SanitizeLine(line, string, endOfFile, true);

    uint8_t i = 0;

    for (; line[i] != '.'; i++) {
        if (line[i] != ' ' || line[i] != '\0') {
            return NO_SUFFIX;
        }
    }

    i++;

    if (line[i] == 's') {
        if (line[i + 2] == 's') {
            return SUFFIX_SIS;
        } else if (line[i + 2] == 'l') {
            return SUFFIX_SIL;
        }
    } else if (line[i] == 'l') {
        if (line[i + 2] == 's') {
            return SUFFIX_LIS;
        } else if (line[i + 2] == 'l') {
            return SUFFIX_LIL;
        }
    }

    return NO_SUFFIX;
}

struct error_t assembler_Main(struct context_t *studioContext) {
    asm_spi_BeginFrame(); // Stop display updates since we use the other buffer
    asm_misc_ClearBuffer(OUTPUT);
    memset((void *)SYMBOL_TABLE, '\0', sizeof(char) * MAX_SYMBOL_TABLE);

    *(char *)(SYMBOL_TABLE) = '$';
    *(uint8_t *)(SYMBOL_TABLE + 2) = 3; 

    char *string = (char *)EDIT_BUFFER;
    static char line[MAX_LINE_LENGTH_ASM];

    void *offset = (void *)os_userMem;
    void *symbolEntry = (void *)SYMBOL_TABLE + sizeof(char) * 3 + sizeof(void *);
    dbg_printf("Symbol Table Start: %p\n", symbolEntry);

    struct error_t error = {0, ERROR_SUCCESS};
    unsigned int result; // Use this for values we have to save occasionally
    struct opcode_t *opcode;

    while (string <= studioContext->openEOF) {
        *(void **)(SYMBOL_TABLE + 3) = offset; // Update $ equate
        error.line += 1;
        assembler_SanitizeLine(line, string, studioContext->openEOF, false);

        dbg_printf("%s |", line);

        if (assembler_IsLabel(line)) {
            dbg_printf("Label @ Offset %p | ", offset);
            strncpy(symbolEntry, line, strlen(line) - 1); // Skip ':' at the end of label names
            symbolEntry += strlen(line); // One extra byte for '\0'
            *(uint8_t *)symbolEntry = 3;
            symbolEntry++;
            *(void **)symbolEntry = offset;
            symbolEntry += 3;
        } else if (assembler_IsEquate(line)) {
            dbg_printf("Equate @ Table %p | ", symbolEntry);
            char *lineCurChar = line;

            for (; *lineCurChar != ' '; lineCurChar++);

            strncpy(symbolEntry, line, lineCurChar - line);
            symbolEntry += lineCurChar - line + 1;
            lineCurChar++;

            for (; *lineCurChar != ' '; lineCurChar++);

            *(uint8_t *)symbolEntry = sizeof(unsigned long);
            symbolEntry++;
            *(unsigned long *)symbolEntry = parser_Eval(++lineCurChar, &(error.code));

            symbolEntry += sizeof(long);
        } else if ((result = assembler_GetDataSize(line))) {
            offset += result;
        } else if ((result = assembler_ReserveBytes(line, string, studioContext->openEOF, &(error.code)))) {
            offset += result;
        } else if ((opcode = asm_misc_FindOpcode(line))) {
            offset += opcode->size;
            dbg_printf("Size %u", opcode->size);

            if (opcode >= &asm_opcodes_AfterCB && opcode < &asm_opcodes_AfterDDCB) {
                offset++;
                dbg_printf(" (+ 1)");
            } else if (opcode >= &asm_opcodes_AfterDDCB) {
                offset += 3;
                dbg_printf(" (+ 3)");
            }

            if ((result = assembler_GetSuffix(line, string, studioContext->openEOF, &(error.code)))) {
                if (result == SUFFIX_LIS || SUFFIX_SIL) {
                    offset++;
                } else if (result == SUFFIX_SIS && opcode->size == 4) {
                    offset--;
                }
            }

            dbg_printf(" | ");
            // Check table location to properly adjust for size
        } else if (*line != '\0') {
            error.code = ERROR_INVAL_TOK;
            return error;
        }

        if (error.code) {
            return error;
        }

        if (symbolEntry > (void *)SYMBOL_TABLE + MAX_SYMBOL_TABLE) {
            error.code = ERROR_MAX_SYMBOLS;
            return error;
        }

        while (*string != '\n' && string <= studioContext->openEOF) {
            string++;
        }

        string++;

        dbg_printf("%s\n", line);
    }

    error.line = 0;

    if (offset - (void *)os_userMem + 2 > MAX_FILE_SIZE) {
        error.code = ERROR_TOO_LARGE;
        return error;
    }

    char *output = (char *)(OUTPUT + 2);
    string = (char *)EDIT_BUFFER;

    strcpy((char *)OUTPUT, OUTPUT_HEADER);

    while (string <= studioContext->openEOF) {
        *(void **)(SYMBOL_TABLE + 3) = os_userMem + ((uint8_t *)output - OUTPUT) - 2;
        error.line += 1;
        assembler_SanitizeLine(line, string, studioContext->openEOF, false);

        dbg_printf("%s |", line);

        if ((result = assembler_GetDataSize(line))) {
            assembler_SanitizeLine(line, string, studioContext->openEOF, true);
            error.code = assembler_WriteData(output, line);

            output += result;
        } else if ((result = assembler_ReserveBytes(line, string, studioContext->openEOF, &(error.code)))) {
            output += result;
        } else if ((opcode = asm_misc_FindOpcode(line))) {
            dbg_printf("\nOutput: %p\n", output);
            assembler_SanitizeLine(line, string, studioContext->openEOF, true);

            if (opcode >= &asm_opcodes_AfterCB && opcode < &asm_opcodes_AfterDD) {
                *(output++) = 0xCB;
            } else if (opcode >= &asm_opcodes_AfterDD && opcode < &asm_opcodes_AfterED) {
                *(output++) = 0xDD;
            } else if (opcode >= &asm_opcodes_AfterED && opcode < &asm_opcodes_AfterFD) {
                *(output++) = 0xED;
            } else if (opcode >= &asm_opcodes_AfterFD && opcode < &asm_opcodes_AfterDDCB) {
                *(output++) = 0xFD;
            } else if (opcode >= &asm_opcodes_AfterDDCB && opcode < &asm_opcodes_AfterFDCB) {
                *(output++) = 0xDD;
                *(output++) = 0xCB;
            } else if (opcode >= &asm_opcodes_AfterFDCB) {
                *(output++) = 0xFD;
                *(output++) = 0xCB;
            }

            memcpy(output, &opcode->data, opcode->size);
            error.code = assembler_PutArgs(output, line, opcode);

            output += opcode->size;
            dbg_printf("Size %u", opcode->size);

            dbg_printf(" | ");
            // Check table location to properly adjust for size
        }

        if (error.code) {
            return error;
        }

        while (*string != '\n' && string <= studioContext->openEOF) {
            string++;
        }

        string++;
    }

    error.line = 0;
    error.code = asm_files_CreateProg(studioContext->fileSize, studioContext->fileName);

    while (kb_AnyKey());
    asm_spi_EndFrame();
    return error;
}
