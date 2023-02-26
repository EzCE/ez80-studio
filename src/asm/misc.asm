;--------------------------------------
;
; ez80 Studio Source Code - files.asm
; By RoccoLox Programs and TIny_Hacker
; Copyright 2022 - 2023
; License: GPL-3.0
;
;--------------------------------------

    assume adl=1

    section .text

include 'include/ti84pceg.inc'

    public _misc_StringToInt

_misc_StringToInt:
    ld iy, 0
    add iy, sp
    ld de, (iy + 3) ; beginning of string
    ld hl, 0
    ld a, (de)
    or a, a
    ret z

.loop:
    cp a, '0'
    jr c, .notANumber
    cp a, '9' + 1
    jr nc, .notANumber
    sub a, '0'
    ld bc, 0
    ld c, a
    add hl, bc
    inc de
    ld a, (de)
    or a, a
    ret z
    add hl, hl
    push hl
    pop bc
    add hl, hl
    add hl, hl
    add hl, bc
    jr .loop

.notANumber:
    ld hl, -1
    ret
