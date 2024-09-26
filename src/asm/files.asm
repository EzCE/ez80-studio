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

    public _asm_files_ReadFile
    public _asm_files_WriteFile
    public _asm_files_CheckFileExists
    public _asm_files_CountLines
    public _asm_files_GetLineLength
    public _asm_files_NextLine
    public _asm_files_PreviousLine
    public _asm_files_InsertChar
    public _asm_files_DeleteChar
    public _asm_files_CreateProg

    extern _asm_misc_ClearBuffer

_asm_files_ReadFile:
    pop de
    ex (sp), hl
    push de
    ex de, hl
    ld hl, ti.OP1
    ld (hl), ti.AppVarObj
    inc hl
    ld bc, 8
    ex de, hl
    ldir ; move name to OP1
    call ti.ChkFindSym
    res 0, a
    ret c
    push de
    push bc
    ld hl, editBuffer - 2
    call _asm_misc_ClearBuffer + 3
    pop bc
    pop de
    call ti.ChkInRam
    ex de, hl
    jr z, .inRam
    ld de, 10
    add hl, de
    ld a, c
    ld bc, 0
    ld c, a
    add hl, bc

.inRam:
    ld bc, 0
    ld c, (hl)
    inc hl
    ld b, (hl) ; get file size
    inc hl
    ld de, editBuffer - 2

.loop:
    ld a, b
    or a, c
    jr z, .return
    ldir

.return:
    ld a, 1
    ret

_asm_files_WriteFile:
    ld iy, 0
    add iy, sp
    ld de, (iy + 6)
    ld hl, 128 ; be safe
    add hl, de
    call ti.EnoughMem
    jr nc, .continue
    xor a, a
    ret

.continue:
    pop de
    ex (sp), hl
    push de
    ex de, hl
    push de
    ld iy, ti.flags
    ld hl, ti.OP1
    ld (hl), ti.AppVarObj
    inc hl
    ld bc, 8
    ex de, hl
    ldir ; move name to OP1
    call ti.ChkFindSym
    jr c, .createFile
    call ti.ChkInRam
    call ti.DelVarArc

.createFile:
    pop de
    ld hl, ti.OP1
    ld (hl), ti.AppVarObj
    inc hl
    ld bc, 8
    ex de, hl
    ldir ; move name to OP1
    ld iy, 0
    add iy, sp
    ld hl, (iy + 6)
    call ti.CreateAppVar
    inc de
    inc de
    ld hl, editBuffer - 2
    ldir
    call ti.OP4ToOP1
    call ti.Arc_Unarc
    ld a, 1
    ret

_asm_files_CheckFileExists:
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

_asm_files_CountLines:
    ld iy, 0
    add iy, sp
    ld hl, (iy + 9) ; end of file
    ld (EOF), hl
    ld hl, editBuffer ; data start
    push iy ; save this for later
    ld de, 1 ; line count
    ld bc, 1 ; newline count
    ld iyl, c ; character count

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
    ld hl, (iy + 3)
    ld (hl), bc
    ld hl, (iy + 6)
    ld (hl), de
    ret

_asm_files_GetLineLength:
    ld iy, 0
    add iy, sp
    ld hl, (iy + 6) ; EOF
    ld (EOF), hl
    ld hl, (iy + 3) ; current address
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

_asm_files_NextLine:
    ld iy, 0
    add iy, sp
    ld hl, (iy + 3) ; current address
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

_asm_files_PreviousLine:
    ld iy, 0
    add iy, sp
    ld hl, (iy + 6) ; end of file
    ld (EOF), hl
    ld hl, (iy + 3) ; current address
    ld (oldLineStart), hl
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
    push hl
    push bc
    push hl
    pop bc
    call _checkEOF
    pop bc
    pop hl
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
    ld hl, editBuffer - 2 + 2
    dec hl
    xor a, a
    sbc hl, de
    ex de, hl
    ret

_asm_files_InsertChar:
    ld iy, 0
    add iy, sp
    ld hl, (iy + 6) ; end of file
    ld bc, (iy + 9) ; size to copy
    push hl
    pop de
    inc de

.loop:
    ld a, b
    or a, c
    jr z, .return
    ldd
    jr .loop

.return:
    ld a, (iy + 3) ; character
    inc hl
    ld (hl), a
    ret

_asm_files_DeleteChar:
    ld iy, 0
    add iy, sp
    ld hl, (iy + 3) ; what to start deleting
    ld bc, (iy + 6) ; size to copy
    push hl
    pop de
    inc hl

.loop:
    ld a, b
    or a, c
    jr z, .return
    ldi
    jr .loop

.return:
    dec hl
    ld (hl), 0
    ret

_asm_files_CreateProg:
    pop de
    pop bc
    ex (sp), hl
    push bc
    push de
    call ti.SetBCUTo0
    push bc
    dec hl
    call ti.Mov9ToOP1
    ld a, ti.ProtProgObj
    ld (ti.OP1), a
    pop bc
    push bc
    ld hl, 128
    add hl, bc
    call ti.EnoughMem
    ld a, 2
    pop bc
    ret c
    push bc
    call ti.ChkFindSym
    call nc, ti.DelVarArc
    pop hl
    push hl
    call ti.CreateProtProg
    pop bc
    ld hl, ti.vRam
    inc de
    inc de
    ldir
    xor a, a
    ret

_checkEOF: ; bc = current address being read; destroys hl and a
    ld hl, (EOF)
    inc hl
    or a, a
    sbc hl, bc
    ret nc
    cp a, a
    ret
