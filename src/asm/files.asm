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

    public _files_CheckFileExists
    public _files_CountLines
    public _files_GetEOF
    public _files_GetLineLength
    public _files_NextLine
    public _files_PreviousLine

EOF := ti.appData

currentLineStart := EOF + 3
oldLineStart := currentLineStart + 3
fileStart := oldLineStart + 3

_files_CheckFileExists:
    ld iy, 0
    add iy, sp
    ld de, (iy + 3) ; name of file
    ld hl, ti.OP1
    ld (hl), ti.AppVarObj
    inc hl
    ld bc, 8
    ex de, hl
    ldir ; move name to OP1
    call ti.ChkFindSym
    ld a, 0
    ret c
    inc a
    ret

_files_CountLines:
    ld iy, 0
    add iy, sp
    ld de, (iy + 3) ; name of file
    push iy ; save this for later
    ld hl, ti.OP1
    ld (hl), ti.AppVarObj
    inc hl
    ld bc, 8
    ex de, hl
    ldir ; move name to OP1
    call ti.ChkFindSym
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
    ld de, 1 ; line count
    ld bc, 1 ; newline count
    ld iyl, 1 ; character count

.loop:
    push bc
    push hl
    push hl
    pop bc
    call _checkEOF
    pop hl
    pop bc
    jr z, .return
    ld a, $0A
    cp a, (hl)
    jr z, .hitNewline
    ld a, 38
    cp a, iyl
    jr z, .hitMaxChars
    inc iyl
    inc hl
    jr .loop

.hitMaxChars:
    inc hl
    ld a, $0A
    cp a, (hl)
    jr z, .hitNewline
    ld iyl, 1
    inc de
    jr .loop

.hitNewline:
    inc bc
    inc de
    ld iyl, 1
    inc hl
    jr .loop

.return:
    pop iy
    ld hl, (iy + 6)
    ld (hl), bc
    ld hl, (iy + 9)
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
    cp a, a
    ret

_getEOF: ; args: hl = size of var; de = start of variable; preserves both registers
    push hl
    dec hl
    add hl, de
    ld (EOF), hl
    pop hl
    ret
