/**
 * --------------------------------------
 * 
 * eZ80 Studio Source Code - fontCherry.c
 * By RoccoLox Programs and TIny_Hacker
 * 
 * Cherry font by turquoise-hexagon
 * Slighly modified from the original
 * 
 * Copyright 2022 - 2025
 * License: GPL-3.0
 * 
 * --------------------------------------
**/

#include "fontCherry.h"

static const uint8_t fontCherryData[] = {
	#include "fontCherry.inc"
};

const fontlib_font_t *fontCherry = (fontlib_font_t *)fontCherryData;
