/**
 * --------------------------------------
 * 
 * ez80 Studio Source Code - main.c
 * By RoccoLox Programs and TIny_Hacker
 * Copyright 2022 - 2023
 * License: GPL-3.0
 * Last Build: January 1, 2023
 * Version: 0.1
 * 
 * --------------------------------------
**/

#include "gfx/gfx.h"
#include "font/fontCherry.h"
#include "defines.h"
#include "ui.h"
#include "menu.h"
#include "utility.h"

#include <graphx.h>
#include <keypadc.h>
#include <fileioc.h>

int main(void) {
    struct preferences *studioPreferences = malloc(sizeof(struct preferences));
    struct context *studioContext = malloc(sizeof(struct context));

    util_ReadPrefs(studioPreferences);

    fontlib_SetFont(fontCherry, 0);
    fontlib_SetForegroundColor(TEXT_DEFAULT);
    fontlib_SetNewlineOptions(1);
    fontlib_SetTransparency(true);

    gfx_Begin();

    if (studioPreferences->theme) {
        gfx_SetPalette(darkPalette, sizeof_darkPalette, 0);
    } else {
        gfx_SetPalette(lightPalette, sizeof_lightPalette, 0);
    }

    gfx_SetDrawBuffer();
    gfx_ZeroScreen();
    ui_NoFile();

    gfx_BlitBuffer();

    while (kb_AnyKey());

    while (!kb_IsDown(kb_KeyClear)) {
        kb_Scan();

        if (kb_IsDown(kb_KeyYequ)) {
            menu_File(studioContext);
            ui_NoFile(); // Change this later when you can open files
            gfx_BlitBuffer();
        } else if (kb_IsDown(kb_KeyWindow)) {
            menu_Compile(studioContext);
            ui_NoFile();
            gfx_BlitBuffer();
        } else if (kb_IsDown(kb_KeyZoom)) {
            menu_Labels(studioContext);
            ui_NoFile();
            gfx_BlitBuffer();
        } else if (kb_IsDown(kb_KeyTrace)) {
            menu_Chars();
            ui_NoFile();
            gfx_BlitBuffer();
        } else if (kb_IsDown(kb_KeyGraph)) {
            menu_Settings(studioPreferences);
            ui_NoFile();
            gfx_BlitBuffer();
        }
    }

    gfx_End();

    util_WritePrefs(studioPreferences);

    return 0;
}
