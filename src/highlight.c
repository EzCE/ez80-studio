/**
 * --------------------------------------
 * 
 * eZ80 Studio Source Code - highlight.c
 * By RoccoLox Programs and TIny_Hacker
 * Copyright 2022 - 2025
 * License: GPL-3.0
 * 
 * --------------------------------------
**/

#include "highlight.h"
#include "lexer.h"
#include "defines.h"

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

char *hlight_GetTokenString(char *string, char *stringEnd) {
    static char stringConvert[MAX_TOK_LENGTH_HL];

    for (uint8_t i = 0; i < stringEnd - string; i++) { // Convert caps to lowercase
        stringConvert[i] = string[i];

        if (stringConvert[i] >= 'A' && stringConvert[i] <= 'Z') {
            stringConvert[i] += 'a' - 'A';
        } 
    }

    stringConvert[stringEnd - string] = '\0';

    return stringConvert;
}

bool hlight_Number(char *string, char *stringEnd) {
    uint8_t numberType = NUMBER_DEC;

    if (*string == '$') {
        numberType = NUMBER_HEX;
    } else if (*string == '0' && *(string + 1) == 'x') {
        numberType = NUMBER_HEX;
        string++;
    } else if (*string == '@') {
        numberType = NUMBER_OCT;
    } else if (*string == '%') {
        numberType = NUMBER_BIN;
    } else {
        string--;
    }

    string++;

    if (string == stringEnd && numberType != NUMBER_DEC) {
        return false;
    }

    while (string != stringEnd) {
        if (numberType == NUMBER_HEX &&
            !((*string >= '0' && *string <= '9') ||
            (*string >= 'A' && *string <= 'F') ||
            (*string >= 'a' && *string <= 'f'))) {

            return false; // Not a valid number
        } else if (numberType == NUMBER_DEC && (*string < '0' || *string > '9')) {
            return false;
        } else if (numberType == NUMBER_OCT && (*string < '0' || *string > '7')) {
            return false;
        } else if (numberType == NUMBER_BIN && (*string < '0' || *string > '1')) {
            return false;
        }

        string++;
    }

    return true; // Number is valid
}

uint8_t hlight_GetHighlightColor(char *string, char *stringEnd, bool highlighting) {
    if (!highlighting) {
        return TEXT_DEFAULT;
    }

    if (*(stringEnd - 1) == ':' && stringEnd - 1 != string) {
        return TEXT_LABEL;
    }

    if ((*string >= 'A' && *string <= 'z') || *string == '.') {
        uint8_t highlightColor = asm_lexer_TokType(string, stringEnd);

        if (highlightColor) {
            return (highlightColor == TEXT_MODIFIER) ? TEXT_INSTRUCTION : highlightColor;
        }
    }

    if ((*string >= '0' && *string <= '9') || *string == '$' || *string == '@' || *string == '%') {
        if (hlight_Number(string, stringEnd)) {
            return TEXT_NUMBER;
        }
    } else if (*string == '(' || *string == ')') {
        return TEXT_PARENTHESIS;
    }

    return TEXT_DEFAULT;
}
