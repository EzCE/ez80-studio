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
    public _files_GetEOF
    public _files_GetLineLength
    public _files_NextLine
    public _files_PreviousLine

EOF := ti.appData
newlineCountPtr := EOF + 3
newlineCount := newlineCountPtr + 3 ; number of newline characters
lineCountPtr := newlineCount + 3
lineCount := lineCountPtr + 3 ; number of actual lines (includes word wrap)

currentLineStart := lineCount + 3
oldLineStart := currentLineStart + 3
fileStart := oldLineStart + 3

_files_CountLines: ; I give up on this so Rocco can just fix it xD
    push ix
    ld ix, 0
    add ix, sp
    ld hl, (ix + 6) ; name of file
    ld de, (ix + 9) ; pointer to int containing number of newline characters
    ld bc, (ix + 12) ; pointer to int containing number of total lines
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
    jr z, .inRam
    ld hl, 10
    add hl, de
    ld a, c
    ld bc, 0
    ld c, a
    add hl, bc
    ex de, hl

.inRam:
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
    ld b, 37

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
    cp a, (hl) ; skip extra newline if line was exactly the max length
    jr z, .newline
    inc hl
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
    ld b, 37
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

_files_GetEOF:
    push ix
    ld ix, 0
    add ix, sp
    ld de, (ix + 6) ; name of file
    pop ix
    ld hl, ti.OP1
    ld (hl), ti.AppVarObj
    inc hl
    ld bc, 8
    ex de, hl
    ldir ; move name to OP1
    call ti.ChkFindSym
    ret c
    call ti.ChkInRam
    jr z, .inRam
    ld hl, 10
    add hl, de
    ld a, c
    ld bc, 0
    ld c, a
    add hl, bc
    ex de, hl

.inRam:
    ld hl, 0
    ld a, (de)
    ld l, a
    inc de
    ld a, (de)
    ld h, a ; get program size
    inc de
    call _getEOF
    ld hl, (EOF)
    ret

_files_GetLineLength:
    push ix
    ld ix, 0
    add ix, sp
    ld hl, (ix + 9) ; EOF
    ld (EOF), hl
    ld hl, (ix + 6) ; current address
    pop ix
    ld bc, 0
    ld b, 38 ; max chars per line

.loop:
    ld a, $0A ; newline
    cp a, (hl)
    jr z, .return

.loopNext:
    push bc
    push hl
    pop bc
    call _checkEOF
    push bc
    pop hl
    pop bc
    jr z, .return
    inc c
    inc hl
    djnz .loop

.return:
    ld a, c
    ret

_files_NextLine:
    push ix
    ld ix, 0
    add ix, sp
    ld hl, (ix + 6) ; current address
    pop ix
    ld b, 38 ; max chars per line

.loop:
    ld a, $0A
    cp a, (hl)
    jr z, .return
    inc hl
    djnz .loop
    cp a, (hl) ; skip extra newline if line was exactly the max length
    jr z, .return
    dec hl

.return:
    inc hl
    ret

_files_PreviousLine:
    push ix
    ld ix, 0
    add ix, sp
    ld hl, (ix + 9) ; start of file
    ld (fileStart), hl
    ld hl, (ix + 6) ; current address
    ld (oldLineStart), hl
    pop ix
    dec hl
    ld a, $0A
    cp a, (hl)
    jr nz, .loopFindStart
    dec hl

.loopFindStart:
    ld a, $0A ; newline
    cp a, (hl)
    jr z, .next
    ld a, $7A ; start of file header
    cp a, (hl)
    call z, .checkFileStart
    jr z, .next
    dec hl
    jr .loopFindStart

.next:
    inc hl ; skip newline
    ld b, 38
    ld (currentLineStart), hl

.loop:
    ld a, $0A
    cp a, (hl)
    jr z, .return
    inc hl
    djnz .loop
    cp a, (hl) ; skip extra newline if line was exactly the max length
    jr z, .loopNext
    dec hl

.loopNext:
    inc hl
    push hl
    ex de, hl
    ld hl, (oldLineStart)
    xor a, a
    sbc hl, de
    pop hl
    jr z, .return
    ld (currentLineStart), hl
    ld b, 38
    jr .loop

.return:
    ld hl, (currentLineStart)
    ret

.checkFileStart:
    ex de, hl
    ld hl, (fileStart)
    dec hl
    xor a, a
    sbc hl, de
    ex de, hl
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
