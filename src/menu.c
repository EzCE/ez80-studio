/**
 * --------------------------------------
 * 
 * ez80 Studio Source Code - menu.c
 * By RoccoLox Programs and TIny_Hacker
 * Copyright 2022 - 2023
 * License: GPL-3.0
 * 
 * --------------------------------------
**/

#include "defines.h"
#include "menu.h"
#include "utility.h"
#include "ui.h"

#include <graphx.h>
#include <fontlibc.h>
#include <keypadc.h>
#include <sys/timers.h>

void menu_File(struct context *studioContext) {
    ui_DrawUIMain(1);
    gfx_SwapDraw();

    while (kb_AnyKey()); // Wait for key to be released

    ui_DrawMenuBox(0, 168, 73, 55, 0);

    fontlib_SetForegroundColor(TEXT_DEFAULT);
    fontlib_SetCursorPosition(4, 174);
    fontlib_DrawString("New file");
    fontlib_SetCursorPosition(4, 191);
    fontlib_DrawString("Open file");
    fontlib_SetCursorPosition(4, 208);
    fontlib_DrawString("Save file");

    gfx_BlitBuffer(); // Since we saved the "unpressed" button, we bring it back now that it isn't pressed anymore, with the menu

    uint8_t option = 0;

    bool keyPressed = false;
    timer_Enable(1, TIMER_32K, TIMER_NOINT, TIMER_UP);
    timer_Set(1, 0);

    while (!kb_IsDown(kb_KeyClear) && !kb_IsDown(kb_KeyYequ) && !kb_IsDown(kb_Key2nd) && !kb_IsDown(kb_KeyEnter)) {
        kb_Scan();

        if (!kb_AnyKey()) {
            keyPressed = false;
            timer_Set(1, 0);
        }

        if (kb_Data[7] && (!keyPressed || timer_Get(1) > 3000)) {
            if (kb_IsDown(kb_KeyUp)) {
                if (option == 0) { // Loop the cursor
                    option = 2;
                } else {
                    option -= 1;
                }
            } else if (kb_IsDown(kb_KeyDown)) {
                if (option == 2) { // Loop the cursor
                    option = 0;
                } else {
                    option += 1;
                }
            }

            ui_DrawMenuBox(0, 168, 73, 55, option);

            fontlib_SetCursorPosition(4, 174);
            fontlib_DrawString("New file");
            fontlib_SetCursorPosition(4, 191);
            fontlib_DrawString("Open file");
            fontlib_SetCursorPosition(4, 208);
            fontlib_DrawString("Save file");

            gfx_BlitBuffer();

            if (!keyPressed) {
                while (timer_Get(1) < 9000 && kb_Data[7]) {
                    kb_Scan();
                }
            }

            keyPressed = true;
            timer_Set(1,0);
        }
    }

    if (kb_IsDown(kb_KeyYequ)) { // Ensure the menu doesn't get opened again immediately
        ui_DrawUIMain(1);
        gfx_BlitBuffer();

        while (kb_AnyKey());
    }
}

void menu_Compile(struct context *studioContext) {
    ui_DrawUIMain(2);
    gfx_SwapDraw();

    while (kb_AnyKey()); // Wait for key to be released

    // Do more here later!
}

void menu_Labels(struct context *studioContext) {
    ui_DrawUIMain(3);
    gfx_SwapDraw();

    while (kb_AnyKey()); // Wait for key to be released

    // Do more here later!
}

void menu_Chars(void) {
    ui_DrawUIMain(4);
    gfx_SwapDraw();

    while (kb_AnyKey()); // Wait for key to be released

    // Do more here later!
}

void menu_Settings(struct context *studioPreferences) {
    ui_DrawUIMain(5);
    gfx_SwapDraw();

    while (kb_AnyKey()); // Wait for key to be released

    ui_DrawMenuBox(255, 202, 55, 21, 0);

    fontlib_SetForegroundColor(TEXT_DEFAULT);
    fontlib_SetCursorPosition(261, 208);
    fontlib_DrawString("Themes");

    gfx_BlitBuffer(); // Since we saved the "unpressed" button, we bring it back now that it isn't pressed anymore, with the menu

    uint8_t option = 0;

    bool keyPressed = false;
    timer_Enable(1, TIMER_32K, TIMER_NOINT, TIMER_UP);
    timer_Set(1, 0);

    while (!kb_IsDown(kb_KeyClear) && !kb_IsDown(kb_KeyGraph) && !kb_IsDown(kb_Key2nd) && !kb_IsDown(kb_KeyEnter)) {
        kb_Scan();

        if (!kb_AnyKey()) {
            keyPressed = false;
            timer_Set(1, 0);
        }

        if (kb_Data[7] && (!keyPressed || timer_Get(1) > 3000)) {
            if (kb_IsDown(kb_KeyUp)) {
                if (option == 0) { // Loop the cursor
                    option = 0;
                } else {
                    option -= 1;
                }
            } else if (kb_IsDown(kb_KeyDown)) {
                if (option == 0) { // Loop the cursor
                    option = 0;
                } else {
                    option += 1;
                }
            }

            ui_DrawMenuBox(255, 202, 55, 21, option);

            fontlib_SetCursorPosition(261, 208);
            fontlib_DrawString("Themes");

            gfx_BlitBuffer();

            if (!keyPressed) {
                while (timer_Get(1) < 9000 && kb_Data[7]) {
                    kb_Scan();
                }
            }

            keyPressed = true;
            timer_Set(1,0);
        }
    }

    if (kb_IsDown(kb_KeyGraph)) { // Ensure the menu doesn't get opened again immediately
        ui_DrawUIMain(5);
        gfx_BlitBuffer();

        while (kb_AnyKey());
    }
}
