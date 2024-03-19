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
    public _asm_misc_GetCharFromKey

    extern _rodata_characters
    extern _rodata_sizeOfCharsLUT

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

_asm_misc_GetCharFromKey: ; Scans for a keypress and converts it to a character
    di
    ld hl, $F50200
    ld (hl), h
    xor a, a

.loop:
    cp a, (hl)
    jr nz, .loop
    ld hl, ti.mpKeyRange + ti.keyData
    ld bc, 56 shl 8

.getKeyLoop:
    ld a, b
    and a, 7
    jr nz, .sameGroup
    inc hl
    inc hl
    ld e, (hl)

.sameGroup:
    sla e
    jr nc, .loopCode
    xor a, a
    cp a, c
    jr nz, .return
    ld c, b

.loopCode:
    djnz .getKeyLoop

.return:
    pop de
    ex (sp), hl
    push de
    ld h, _rodata_sizeOfCharsLUT
    mlt hl
    ld de, _rodata_characters
    add hl, de
    ld a, c
    sub a, 9
    jr c, $ + 8
    cp a, _rodata_sizeOfCharsLUT + 1
    jr nc, $ + 4
    ld c, a
    add hl, bc
    ld a, (hl)
    ret
