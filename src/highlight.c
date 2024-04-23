/**
 * --------------------------------------
 * 
 * eZ80 Studio Source Code - highlight.c
 * By RoccoLox Programs and TIny_Hacker
 * Copyright 2022 - 2024
 * License: GPL-3.0
 * 
 * --------------------------------------
**/

#include "highlight.h"
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

bool hlight_Condition(char *string, char *stringEnd) {
    if (stringEnd - string > 2) {
        return false;
    }

    char *stringConvert = hlight_GetTokenString(string, stringEnd);

    if (stringEnd - string == 1) { // We don't check for 'c' because it's counted by the register as well, and they are highlighted the same
        if (*stringConvert == 'z' ||
            *stringConvert == 'm' ||
            *stringConvert == 'p') {
            return true;
        }
    } else {
        if (!strcmp("nz", stringConvert) ||
            !strcmp("nc", stringConvert) ||
            !strcmp("pe", stringConvert) ||
            !strcmp("po", stringConvert)) {
            return true;
        }
    }

    return false;
}

bool hlight_Register(char *string, char *stringEnd) {
    if (stringEnd - string > 3) {
        return false;
    }

    char *stringConvert = hlight_GetTokenString(string, stringEnd);

    if (stringEnd - string == 1) {
        if (*stringConvert == 'a' || *stringConvert == 'f' ||
            *stringConvert == 'b' || *stringConvert == 'c' ||
            *stringConvert == 'd' || *stringConvert == 'e' ||
            *stringConvert == 'h' || *stringConvert == 'l' ||
            *stringConvert == 'i' || *stringConvert == 'r') {
            return true;
        }
    } else if (stringEnd - string == 2) {
        if (!strcmp("af", stringConvert) ||
            !strcmp("bc", stringConvert) ||
            !strcmp("de", stringConvert) ||
            !strcmp("hl", stringConvert) ||
            !strcmp("ix", stringConvert) ||
            !strcmp("iy", stringConvert) ||
            !strcmp("sp", stringConvert) ||
            !strcmp("mb", stringConvert)) {
            return true;
        }
    } else {
        if (!strcmp("af\'", stringConvert) ||
            !strcmp("ixh", stringConvert) ||
            !strcmp("ixl", stringConvert) ||
            !strcmp("iyh", stringConvert) ||
            !strcmp("iyl", stringConvert)) {
            return true;
        }
    }

    return false;
}

bool hlight_Instruction(char *string, char *stringEnd) {
    if ((stringEnd - string > 5) || (stringEnd - string < 2)) {
        return false;
    }

    char *stringConvert = hlight_GetTokenString(string, stringEnd);

    if (stringEnd - string == 2) {
        if (!strcmp("cp", stringConvert) ||
            !strcmp("ex", stringConvert) ||
            !strcmp("in", stringConvert) ||
            !strcmp("ld", stringConvert) ||
            !strcmp("or", stringConvert) ||
            !strcmp("di", stringConvert) ||
            !strcmp("ei", stringConvert) ||
            !strcmp("im", stringConvert) ||
            !strcmp("jp", stringConvert) ||
            !strcmp("jr", stringConvert) ||
            !strcmp("rl", stringConvert) ||
            !strcmp("rr", stringConvert) ||
            !strcmp("db", stringConvert) ||
            !strcmp("dw", stringConvert) ||
            !strcmp("dl", stringConvert) ||
            !strcmp("dd", stringConvert) ||
            !strcmp("dq", stringConvert)) {
            return true;
        }
    } else if (stringEnd - string == 3) {
        if (!strcmp("adc", stringConvert) ||
            !strcmp("add", stringConvert) ||
            !strcmp("daa", stringConvert) ||
            !strcmp("dec", stringConvert) ||
            !strcmp("inc", stringConvert) ||
            !strcmp("mlt", stringConvert) ||
            !strcmp("neg", stringConvert) ||
            !strcmp("sbc", stringConvert) ||
            !strcmp("sub", stringConvert) ||
            !strcmp("bit", stringConvert) ||
            !strcmp("res", stringConvert) ||
            !strcmp("set", stringConvert) ||
            !strcmp("cpd", stringConvert) ||
            !strcmp("cpi", stringConvert) ||
            !strcmp("ldd", stringConvert) ||
            !strcmp("ldi", stringConvert) ||
            !strcmp("exx", stringConvert) ||
            !strcmp("in0", stringConvert) ||
            !strcmp("ind", stringConvert) ||
            !strcmp("ini", stringConvert) ||
            !strcmp("out", stringConvert) ||
            !strcmp("lea", stringConvert) ||
            !strcmp("pea", stringConvert) ||
            !strcmp("pop", stringConvert) ||
            !strcmp("and", stringConvert) ||
            !strcmp("cpl", stringConvert) ||
            !strcmp("tst", stringConvert) ||
            !strcmp("xor", stringConvert) ||
            !strcmp("ccf", stringConvert) ||
            !strcmp("nop", stringConvert) ||
            !strcmp("scf", stringConvert) ||
            !strcmp("slp", stringConvert) ||
            !strcmp("ret", stringConvert) ||
            !strcmp("rst", stringConvert) ||
            !strcmp("rla", stringConvert) ||
            !strcmp("rlc", stringConvert) ||
            !strcmp("rld", stringConvert) ||
            !strcmp("rra", stringConvert) ||
            !strcmp("rrc", stringConvert) ||
            !strcmp("rrd", stringConvert) ||
            !strcmp("sla", stringConvert) ||
            !strcmp("sll", stringConvert) ||
            !strcmp("sra", stringConvert) ||
            !strcmp("srl", stringConvert)) {
            return true;
        }
    } else if (stringEnd - string == 4) {
        if (!strcmp("cpdr", stringConvert) ||
            !strcmp("cpir", stringConvert) ||
            !strcmp("lddr", stringConvert) ||
            !strcmp("ldir", stringConvert) ||
            !strcmp("indr", stringConvert) ||
            !strcmp("ind2", stringConvert) ||
            !strcmp("indm", stringConvert) ||
            !strcmp("ini2", stringConvert) ||
            !strcmp("inim", stringConvert) ||
            !strcmp("otdm", stringConvert) ||
            !strcmp("otim", stringConvert) ||
            !strcmp("out0", stringConvert) ||
            !strcmp("outd", stringConvert) ||
            !strcmp("outi", stringConvert) ||
            !strcmp("push", stringConvert) ||
            !strcmp("halt", stringConvert) ||
            !strcmp("call", stringConvert) ||
            !strcmp("djnz", stringConvert) ||
            !strcmp("reti", stringConvert) ||
            !strcmp("retn", stringConvert) ||
            !strcmp("rlca", stringConvert) ||
            !strcmp("rrca", stringConvert)) {
            return true;
        }
    } else {
        if (!strcmp("ind2r", stringConvert) ||
            !strcmp("indmr", stringConvert) ||
            !strcmp("inirx", stringConvert) ||
            !strcmp("otdmr", stringConvert) ||
            !strcmp("otdrx", stringConvert) ||
            !strcmp("otimr", stringConvert) ||
            !strcmp("otirx", stringConvert) ||
            !strcmp("outd2", stringConvert) ||
            !strcmp("otd2r", stringConvert) ||
            !strcmp("outi2", stringConvert) ||
            !strcmp("oti2r", stringConvert) ||
            !strcmp("tstio", stringConvert) ||
            !strcmp("rsmix", stringConvert) ||
            !strcmp("stmix", stringConvert)) {
            return true;
        }
    }

    return false;
}

static bool hlight_Number(char *string, char *stringEnd) {
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
    }

    string++;

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

bool hlight_Modifier(char *string, char *stringEnd) {
    if (stringEnd - string > 4) {
        return false;
    }

    char *stringConvert = hlight_GetTokenString(string, stringEnd);

    if (stringEnd - string == 2) {
        if (*(stringConvert + 1) == 's' || *(stringConvert + 1) == 'l') {
            return true;
        }
    } else if (stringEnd - string == 4) {
        if (strcmp("sis", stringConvert + 1) == 0 ||
            strcmp("sil", stringConvert + 1) == 0 ||
            strcmp("lis", stringConvert + 1) == 0 ||
            strcmp("lil", stringConvert + 1) == 0) {
            return true;
        }
    }

    return false;
}

uint8_t hlight_GetHighlightColor(char *string, char *stringEnd, bool highlighting) {
    uint8_t highlightColor = TEXT_DEFAULT; // If we don't end up changing the color later, it stays as the default

    if (!highlighting) {
        return TEXT_DEFAULT;
    }

    if (*(stringEnd - 1) == ':' && stringEnd - 1 != string) {
        highlightColor = TEXT_LABEL;
    } else if (*string >= 'A' && *string <= 'z') {
        if (hlight_Condition(string, stringEnd)) {
            highlightColor = TEXT_REGISTER; // Use the same color as registers
        } else if (hlight_Register(string, stringEnd)) {
            highlightColor = TEXT_REGISTER;
        } else if (hlight_Instruction(string, stringEnd)) {
            highlightColor = TEXT_INSTRUCTION;
        }
    } else if ((*string >= '0' && *string <= '9') || *string == '$' || *string == '@' || *string == '%') {
        if (hlight_Number(string, stringEnd)) {
            highlightColor = TEXT_NUMBER;
        }
    } else if (*string == '(' || *string == ')') {
        highlightColor = TEXT_PARENTHESIS;
    } else if (hlight_Modifier(string, stringEnd)) {
        highlightColor = TEXT_INSTRUCTION;
    }

    return highlightColor;
}
