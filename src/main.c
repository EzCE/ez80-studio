/**
 * --------------------------------------
 * 
 * ez80 Studio Source Code - main.c
 * By RoccoLox Programs and TIny_Hacker
 * Copyright 2022 - 2023
 * License: GPL-3.0
 * Last Build: March 16, 2023
 * Version: 0.5.0
 * 
 * --------------------------------------
**/

#include "gfx/gfx.h"
#include "font/fontCherry.h"
#include "asm/files.h"
#include "defines.h"
#include "ui.h"
#include "menu.h"
#include "edit.h"
#include "utility.h"

#include <graphx.h>
#include <keypadc.h>
#include <fileioc.h>
#include <sys/timers.h>

int main(void) {
    struct preferences_t *studioPreferences = malloc(sizeof(struct preferences_t));
    struct context_t *studioContext = malloc(sizeof(struct context_t));

    studioContext->fileName = NULL;
    studioContext->fileIsOpen = false;

    studioContext->lineStart = 0; // The scrollbar will be weird if we don't do this
    studioContext->newlineStart = 0;
    studioContext->totalLines = 0;
    studioContext->newlineCount = 0;

    bool redraw = true;

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

    while (kb_AnyKey());

    while (!kb_IsDown(kb_KeyClear)) {
        kb_Scan();

        if (kb_IsDown(kb_KeyYequ)) {
            menu_File(studioContext, studioPreferences);
            redraw = true;
        } else if (kb_IsDown(kb_KeyWindow)) {
            menu_Compile(studioContext);
            redraw = true;
        } else if (kb_IsDown(kb_KeyZoom)) {
            menu_Goto(studioContext);
            redraw = true;
        } else if (kb_IsDown(kb_KeyTrace)) {
            menu_Chars(studioContext);
            redraw = true;
        } else if (kb_IsDown(kb_KeyGraph)) {
            menu_Settings(studioContext, studioPreferences);
            redraw = true;
        }

        if (studioContext->fileIsOpen) {
            edit_OpenEditor(studioContext, studioPreferences);
        }

        if (redraw) {
            gfx_ZeroScreen();
            ui_NoFile();

            redraw = false;
            gfx_BlitBuffer();
        }
    }

    gfx_End();

    asm("call $00214C0\n\tcall $0020E9C"); // Delete temporary programs

    util_WritePrefs(studioPreferences);

    return 0;
}
