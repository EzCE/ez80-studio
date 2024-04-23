/**
 * --------------------------------------
 * 
 * eZ80 Studio Source Code - main.c
 * By RoccoLox Programs and TIny_Hacker
 * Copyright 2022 - 2024
 * License: GPL-3.0
 * Last Build: April 23, 2024
 * Version: 0.8.4
 * 
 * --------------------------------------
**/

#include "gfx/gfx.h"
#include "font/fontCherry.h"
#include "defines.h"
#include "ui.h"
#include "menu.h"
#include "edit.h"
#include "utility.h"
#include "asm/files.h"
#include "asm/spi.h"

#include <graphx.h>
#include <keypadc.h>
#include <fileioc.h>

int main(void) {
    static struct preferences_t studioPreferences;
    static struct context_t studioContext;

    dbg_printf("Structs: %p | %p - %u\n", &studioPreferences, &studioContext, sizeof(struct context_t));

    studioContext.fileIsOpen = false;

    studioContext.lineStart = 0; // The scrollbar will be weird if we don't do this
    studioContext.newlineStart = 0;
    studioContext.totalLines = 0;
    studioContext.newlineCount = 0;

    util_ReadPrefs(&studioPreferences);

    fontlib_SetFont(fontCherry, 0);
    fontlib_SetForegroundColor(TEXT_DEFAULT);
    fontlib_SetNewlineOptions(1);
    fontlib_SetTransparency(true);

    gfx_Begin();

    if (studioPreferences.theme) {
        gfx_SetPalette(darkPalette, sizeof_darkPalette, 0);
    } else {
        gfx_SetPalette(lightPalette, sizeof_lightPalette, 0);
    }

    edit_RedrawEditor(&studioContext, &studioPreferences);

    while (kb_AnyKey());

    while (!kb_IsDown(kb_KeyClear)) {
        kb_Scan();

        if (kb_IsDown(kb_KeyYequ)) {
            menu_File(&studioContext, &studioPreferences);
            edit_RedrawEditor(&studioContext, &studioPreferences);
            while (kb_AnyKey());
        } else if (kb_IsDown(kb_KeyWindow)) {
            menu_Assemble(&studioContext);
            edit_RedrawEditor(&studioContext, &studioPreferences);
            while (kb_AnyKey());
        } else if (kb_IsDown(kb_KeyZoom)) {
            menu_Goto(&studioContext);
            edit_RedrawEditor(&studioContext, &studioPreferences);
            while (kb_AnyKey());
        } else if (kb_IsDown(kb_KeyTrace)) {
            char insert = menu_Chars(&studioContext);

            if (studioContext.fileSize < MAX_FILE_SIZE && studioContext.fileIsOpen) {
                util_InsertChar(insert, &studioContext);
            }

            edit_RedrawEditor(&studioContext, &studioPreferences);
            while (kb_AnyKey());
        } else if (kb_IsDown(kb_KeyGraph)) {
            menu_Settings(&studioContext, &studioPreferences);
            edit_RedrawEditor(&studioContext, &studioPreferences);
            while (kb_AnyKey());
        }

        if (studioContext.fileIsOpen) {
            edit_OpenEditor(&studioContext, &studioPreferences);
            studioContext.fileIsOpen = false;

            studioContext.lineStart = 0;
            studioContext.newlineStart = 0;
            studioContext.totalLines = 0;
            studioContext.newlineCount = 0;
            edit_RedrawEditor(&studioContext, &studioPreferences);
            while (kb_AnyKey());
        }
    }

    asm_spi_EndFrame(); // Do this to be safe
    gfx_End();

    util_WritePrefs(&studioPreferences);

    return 0;
}
