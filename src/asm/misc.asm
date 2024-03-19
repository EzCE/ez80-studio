;--------------------------------------
;
; eZ80 Studio Source Code - files.asm
; By RoccoLox Programs and TIny_Hacker
; Copyright 2022 - 2024
; License: GPL-3.0
;
;--------------------------------------

    assume adl=1

    section .text

include 'include/equates.inc'

    public _asm_misc_StringToInt
    public _asm_misc_ClearBuffer

_asm_misc_StringToInt:
    pop de
    ex (sp), hl ; beginning of string
    push de
    ex de, hl
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

_asm_misc_ClearBuffer:
    pop de
    ex (sp), hl ; get address to clear
    push de
    ld bc, ti.lcdWidth * ti.lcdHeight
    jp ti.MemClear
