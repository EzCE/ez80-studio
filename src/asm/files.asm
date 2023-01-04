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
newlineCount := newlineCountPtr + 3

_files_CountLines:
	push ix
    ld ix, 0
    add ix, sp
    ld hl, (ix + 6) ; name of file
    ld de, (ix + 9) ; pointer to int containing number of newlines
    pop ix
	ld (newLineCountPtr), de
	ex de, hl
	ld hl, 1
	ld (newLineCount), hl
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

.loop:
	push hl
	pop bc
	call _checkEOF
	jr z, .return
	push bc
	pop hl
	ld a, $3F ; newline so that Celtic detects line count
	cp a, (hl)
	jr z, .newline

.newline:
	ld de, (newlineCount)
	inc de
	ld (newlineCount), de
	inc hl
	jr .loop

.return:

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
