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

    public _files_CountLines

EOF := ti.appData
newlineCountPtr := EOF + 3
newlineCount := newlineCountPtr + 3 ; number of newline characters
lineCountPtr := newlineCount + 3
lineCount := lineCountPtr + 3 ; number of actual lines (includes word wrap)

_files_CountLines:
    push ix
    ld ix, 0
    add ix, sp
    ld hl, (ix + 6) ; name of file
    ld de, (ix + 9) ; pointer to int containing number of newline characters
    ld bc, (ix + 9) ; pointer to int containing number of total lines
    pop ix
    ld (newlineCountPtr), de
    ld (lineCountPtr), bc
    ex de, hl
    ld hl, 1
    ld (newlineCount), hl
    ld (lineCount), hl
    ld hl, ti.OP1
    ld (hl), ti.AppVarObj
    inc hl
    ld bc, 8
    ex de, hl
    ldir ; move name to OP1
    call ti.ChkFindSym
    ret c
    call ti.ChkInRam
    jr z, inRam
    ld hl, 10
    add hl, de
    ld a, c
    ld bc, 0
    ld c, a
    add hl, bc
    ex de, hl

inRam:
    ld hl, 0
    ld a, (de)
    ld l, a
    inc de
    ld a, (de)
    ld h, a ; get program size
    inc de
    call _getEOF
    inc de
    inc de
    ex de, hl
    ld b, 39

.loop:
    push bc
    push hl
    pop bc
    call _checkEOF
    jr z, .return
    push bc
    pop hl
    ld a, $0A
    cp a, (hl)
    pop bc
    jr z, .newlineChar
    inc hl
    djnz .loop
    jr .newline

.newlineChar:
    ld de, (newlineCount)
    inc de
    ld (newlineCount), de

.newline:
    ld de, (lineCount)
    inc de
    ld (lineCount), de
    inc hl
    ld b, 0
    jr .loop

.return:
    pop bc
    ld hl, (newlineCountPtr)
    ld de, (newlineCount)
    ld (hl), de
    ld hl, (lineCountPtr)
    ld de, (lineCount)
    ld (hl), de
    ret

_checkEOF: ; bc = current address being read; destroys hl and a
    ld hl, (EOF)
    inc hl
    or a, a
    sbc hl, bc
    ret nc
    dec de
    cp a, a
    ret

_getEOF: ; args: hl = size of var; de = start of variable; preserves both registers
    push hl
    dec hl
    add hl, de
    ld (EOF), hl
    pop hl
    ret
