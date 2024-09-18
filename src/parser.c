/**
 * --------------------------------------
 * 
 * eZ80 Studio Source Code - parser.c
 * By RoccoLox Programs and TIny_Hacker
 * Copyright 2022 - 2024
 * License: GPL-3.0
 * 
 * --------------------------------------
**/

#include "highlight.h"
#include "parser.h"
#include "utility.h"
#include "asm/misc.h"

#include <stdlib.h>
#include <string.h>

#include <debug.h>

/**
 * Token currently being parsed.
*/
static char *nextToken;

/**
 * Final byte of input.
*/
static char *inputEnd;

/**
 * Error code returned by the parser if necessary.
*/
uint8_t *retErr;

static char *parser_GetTokStart(char *token) {
    bool singleChar = true;

    while (*token != '\0') {
        if (*token == '(' ||
            *token == ')' ||
            *token == '+' ||
            *token == '-' ||
            *token == '*' ||
            *token == '/' ||
            *token == '>' ||
            *token == '<' ||
            *token == '&' ||
            *token == '^' ||
            *token == '|') {

            if (singleChar && (!strncmp(token - 1, "<<", 2) || !strncmp(token - 1, ">>", 2))) {
                return token - 1;
            }

            if (!(*token == '-' && (
                *(token - 1) == '+' ||
                *(token - 1) == '-' ||
                *(token - 1) == '*' ||
                *(token - 1) == '/' ||
                *(token - 1) == '>' ||
                *(token - 1) == '<' ||
                *(token - 1) == '&' ||
                *(token - 1) == '^' ||
                *(token - 1) == '|' ||
                *(token - 1) == '\0'))) {

                return token + !singleChar;
            }
        }

        singleChar = false;
        token--;
    }

    return token + 1;
}

/**
 * Parse bitwise OR
 * BR -> BR | BX
 * BR -> BX
*/
long parser_BR(void) {
    long BX = parser_BX();

    if (*(nextToken - 1) == '\0') {
        return BX;
    }

    if (*nextToken == '|') {
        nextToken = parser_GetTokStart(nextToken - 1);

        dbg_printf(" | ");
        return parser_BR() | BX;
    } else {
        return BX;
    }
}

/**
 * Parse bitwise XOR
 * BX -> BX ^ BA
 * BX -> BA
*/
long parser_BX(void) {
    long BA = parser_BA();

    if (*(nextToken - 1) == '\0') {
        return BA;
    }

    if (*nextToken == '^') {
        nextToken = parser_GetTokStart(nextToken - 1);

        dbg_printf(" ^ ");
        return parser_BX() ^ BA;
    } else {
        return BA;
    }
}

/**
 * Parse bitwise AND
 * BA -> BA & S
 * BA -> S
*/
long parser_BA(void) {
    long S = parser_S();

    if (*(nextToken - 1) == '\0') {
        return S;
    }

    if (*nextToken == '&') {
        nextToken = parser_GetTokStart(nextToken - 1);

        dbg_printf(" & ");
        return parser_BA() & S;
    } else {
        return S;
    }
}

/**
 * Parse left / right bitshift
 * S -> S << E
 * S -> S >> E
 * S -> E
*/
long parser_S(void) {
    long E = parser_E();

    if (*(nextToken - 1) == '\0') {
        return E;
    }

    if (!strncmp(nextToken, "<<", 2)) {
        nextToken = parser_GetTokStart(nextToken - 1);

        dbg_printf(" << ");
        return parser_S() << E;
    } else if (!strncmp(nextToken, ">>", 2)) {
        nextToken = parser_GetTokStart(nextToken - 1);

        dbg_printf(" >> ");
        return parser_S() >> E;
    } else {
        return E;
    }
}

/**
 * Parse expression
 * E -> E + T
 * E -> E - T
 * E -> T
*/
long parser_E(void) {
    long T = parser_T();

    if (*(nextToken - 1) == '\0') {
        return T;
    }

    if (*nextToken == '+') {
        nextToken = parser_GetTokStart(nextToken - 1);

        dbg_printf(" + ");
        return parser_E() + T;
    } else if (*nextToken == '-') {
        nextToken = parser_GetTokStart(nextToken - 1);

        dbg_printf(" - ");
        return parser_E() - T;
    } else {
        return T;
    }
}

/**
 * Parse term
 * T -> T * F
 * T -> T / F
 * T -> F
*/
long parser_T(void) {
    long F = parser_F();

    if (*(nextToken - 1) == '\0') {
        return F;
    }

    if (*nextToken == '*') {
        nextToken = parser_GetTokStart(nextToken - 1);

        dbg_printf(" * ");
        return parser_T() * F;
    } else if (*nextToken == '/') {
        nextToken = parser_GetTokStart(nextToken - 1);

        dbg_printf(" / ");
        return parser_T() / F;
    } else {
        return F;
    }
}

/**
 * Parse factor
 * F -> Symbol
 * F -> Int
 * F -> ( BR )
 * F -> -F
*/
long parser_F(void) {
    char *parseNum;
    parseNum = nextToken;
    nextToken = parser_GetTokStart(nextToken - 1);

    if (hlight_Number(parseNum, util_GetStringEnd(parseNum, inputEnd))) {
        uint8_t base = NUMBER_DEC;

        if (*parseNum == '$') {
            base = NUMBER_HEX;
        } else if (*parseNum == '0' && *(parseNum + 1) == 'x') {
            base = NUMBER_HEX;
            parseNum++;
        } else if (*parseNum == '@') {
            base = NUMBER_OCT;
        } else if (*parseNum == '%') {
            base = NUMBER_BIN;
        } else {
            parseNum--;
        }

        parseNum++;

        dbg_printf("%ld", strtol(parseNum, NULL, base));

        return strtol(parseNum, NULL, base);
    } else if (*parseNum == ')') {
        dbg_printf("(");
        long BR = parser_BR();

        if (*nextToken == '(') {
            dbg_printf(")");
            nextToken = parser_GetTokStart(nextToken - 1);
            return BR;
        } else {
            *retErr = ERROR_INVAL_EXPR;
            return 0;
        }
    } else if (*parseNum == '-') {
        dbg_printf("-");
        nextToken = parseNum;
        nextToken++;
        long F = parser_F();
        nextToken = parser_GetTokStart(parseNum - 1);
        return -F;
    }

    static char symbol[MAX_LINE_LENGTH_ASM];
    strncpy(symbol, parseNum, util_GetStringEnd(parseNum, inputEnd) - parseNum);
    symbol[util_GetStringEnd(parseNum, inputEnd) - parseNum] = '\0';
    void *found = asm_misc_FindSymbol(symbol);

    if (found != NULL) {
        found += strlen(found) + 1;

        memset(symbol, '\0', sizeof(char) * sizeof(long));
        memcpy(symbol, found + 1, *(uint8_t *)found);
        dbg_printf("%ld", *(long *)symbol);
        return *(long *)symbol;
    }

    *retErr = ERROR_INVAL_EXPR;
    return 0;
}

unsigned long parser_Eval(char *input, uint8_t *error) {
    unsigned int length = strlen(input);
    retErr = error;
    asm_misc_ReverseCopy(input + length - 1, input + length, length); // Very cursed parsing reversed
    *input = '\0';
    inputEnd = input + length;
    nextToken = parser_GetTokStart(input + length);
    return parser_BR();
}
