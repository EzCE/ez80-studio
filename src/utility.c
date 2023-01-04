/**
 * --------------------------------------
 * 
 * ez80 Studio Source Code - utility.c
 * By RoccoLox Programs and TIny_Hacker
 * Copyright 2022 - 2023
 * License: GPL-3.0
 * 
 * --------------------------------------
**/

#include "utility.h"
#include "defines.h"

#include <fileioc.h>

static void util_SetDefaults(struct preferences *studioPreferences) {
    studioPreferences->theme = LIGHT_THEME;
}

void util_ReadPrefs(struct preferences *studioPreferences) {
    uint8_t appvar = ti_Open("EzStudio", "r");  // Maybe put this in a separate function later?

    if (appvar) {
        ti_Read(&(studioPreferences->theme), 1, 1, appvar);
    } else {
        util_SetDefaults(studioPreferences);
    }
}

void util_WritePrefs(struct preferences *studioPreferences) {
    uint8_t appvar = ti_Open("EzStudio", "w");
    
    ti_Write(&(studioPreferences->theme), 1, 1, appvar);
    ti_SetArchiveStatus(true, appvar);
}
