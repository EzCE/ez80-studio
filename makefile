#--------------------------------------
#
# eZ80 Studio Source Code - makefile
# By RoccoLox Programs and TIny_Hacker
# Copyright 2022 - 2026
# License: GPL-3.0
#
#--------------------------------------

NAME = EZSTUDIO
ICON = icon.png
DESCRIPTION = "eZ80 Assembly IDE"
COMPRESSED = YES
ARCHIVED = YES
VERSION = 1.1.0

CFLAGS = -Wall -Wextra -Oz -DVERSION_NO=\"$(VERSION)\"
CXXFLAGS = -Wall -Wextra -Oz -DVERSION_NO=\"$(VERSION)\"

FONTDIR = $(SRCDIR)/font
FONT = $(FONTDIR)/fontCherry.fnt
FONT_INC = $(FONTDIR)/fontCherry.inc

DEPS = $(FONT_INC)

# ----------------------------

include $(shell cedev-config --makefile)

$(FONT_INC): $(FONT)
	$(Q)$(call MKDIR,$(@D))
	$(Q)convfont -o carray -f $< -a 1 -b 1 -w bold -c 2 -x 9 -l 0x0B -Z $@

final:
	make
	convbin -r -e zx0 -k 8xp-compressed -u -n $(NAME) -i bin/$(NAME).bin -o bin/$(NAME).8xp
