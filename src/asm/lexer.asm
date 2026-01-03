;--------------------------------------
;
; eZ80 Studio Source Code - lexer.asm
; By RoccoLox Programs and TIny_Hacker
; Copyright 2022 - 2026
; License: GPL-3.0
;
;--------------------------------------

    assume adl=1

    section .text

include 'include/equates.inc'

    public _asm_lexer_TokType

_asm_lexer_TokType:
    pop bc
    pop de ; Start of string
    ex (sp), hl ; End of string
    push de
    push bc
    xor a, a
    sbc hl, de
    ex de, hl
    ld a, (hl)
    dec e
    jp z, _lexer1
    cp a, 'a'
    jr nc, .lowerized
    add a, 'a' - 'A'

.lowerized:
    ld (_smcFirstChar), a
    dec e
    jp z, _lexer2
    dec e
    jr z, _lexer3
    dec e
    jr z, _lexer4
    xor a, a
    dec e
    ret nz

_lexer5:
    ld a, (hl)
    sub a, 'i'
    jp c, _noMatch
    cp a, 'u' + 1 - 'i'
    jp nc, _noMatch
    push hl
    ld hl, _lexer5AlphaLUT
    ld e, a
    add hl, de
    ld e, (hl)
    inc e
    jp z, _noMatchPop
    dec e
    ld hl, _lexer5LUT
    add hl, de
    ld a, 5
    ld (_smcLength), a
    inc a
    ld (_smcLengthPlus1), a
    jr _findMatch

_lexer4:
    cp a, '.' + 'a' - 'A'
    jr nz, .notSuffix
    push hl
    ld hl, _lexer4Suffix
    jr .gotOffset

.notSuffix:
    sub a, 'c'
    jp c, _noMatch
    cp a, 'r' + 1 - 'c'
    jr nc, _noMatch
    push hl
    ld hl, _lexer4AlphaLUT
    ld e, a
    add hl, de
    ld e, (hl)
    inc e
    jr z, _noMatchPop
    dec e
    ld hl, _lexer4LUT
    add hl, de

.gotOffset:
    ld a, 4
    ld (_smcLength), a
    inc a
    ld (_smcLengthPlus1), a
    jr _findMatch

_lexer3:
    sub a, 'a'
    jr c, _noMatch
    cp a, 'x' + 1 - 'a'
    jr nc, _noMatch
    push hl
    ld hl, _lexer3AlphaLUT
    ld e, a
    add hl, de
    ld e, (hl)
    inc e
    jr z, _noMatchPop
    dec e
    ld hl, _lexer3LUT
    add hl, de
    ld a, 3
    ld (_smcLength), a
    inc a
    ld (_smcLengthPlus1), a
    jr _findMatch

_lexer2:
    sub a, 'a'
    jr c, _noMatch
    cp a, 's' + 1 - 'a'
    jr nc, _noMatch
    push hl
    ld hl, _lexer2AlphaLUT
    ld e, a
    add hl, de
    ld e, (hl)
    inc e
    jr z, _noMatchPop
    dec e
    ld hl, _lexer2LUT
    add hl, de
    ld a, 2
    ld (_smcLength), a
    inc a
    ld (_smcLengthPlus1), a

_findMatch:
    ld b, 0
_smcLength := $ - 1
    pop de
    push de
    push hl
    call _compare
    jr z, _found
    pop hl
    ld de, 0
_smcLengthPlus1 := $ - 3
    add hl, de
    ld a, 0
_smcFirstChar := $ - 1
    cp a, (hl)
    jr z, _findMatch

_noMatchPop:
    pop hl

_noMatch:
    xor a, a
    ret

_found:
    ld a, (hl)
    pop de
    pop de
    ret

_compare:
    ld a, (de)
    cp a, 'a'
    jr nc, .lowerized
    add a, 'a' - 'A'

.lowerized:
    cp a, (hl)
    ret nz
    inc hl
    inc de
    djnz _compare
    ret

_lexer1:
    cp a, 'a'
    jr nc, .lowerized
    add a, 'a' - 'A'

.lowerized:
    sub a, 'a'
    jr c, _noMatch
    cp a, 'z' + 1 - 'a'
    jr nc, _noMatch ; also load correct return value
    ld hl, _lexer1LUT
    ld e, a
    add hl, de
    ld a, (hl)
    ret

_lexer5AlphaLUT:
    db _lexer5I - _lexer5LUT ; 'i'
    db 255 ; 'j'
    db 255 ; 'k'
    db 255 ; 'l'
    db 255 ; 'm'
    db 255 ; 'n'
    db _lexer5O - _lexer5LUT ; 'o'
    db 255 ; 'p'
    db 255 ; 'q'
    db _lexer5R - _lexer5LUT ; 'r'
    db _lexer5S - _lexer5LUT ; 's'
    db _lexer5T - _lexer5LUT ; 't'

_lexer5LUT:
_lexer5I:
    db "ind2r", typeInstruction
    db "indmr", typeInstruction
    db "inirx", typeInstruction

_lexer5O:
    db "otdmr", typeInstruction
    db "otdrx", typeInstruction
    db "otimr", typeInstruction
    db "otirx", typeInstruction
    db "outd2", typeInstruction
    db "otd2r", typeInstruction
    db "outi2", typeInstruction
    db "oti2r", typeInstruction

_lexer5R:
    db "rsmix", typeInstruction

_lexer5S:
    db "stmix", typeInstruction

_lexer5T:
    db "tstio", typeInstruction

_lexer4AlphaLUT:
    db _lexer4C - _lexer4LUT ; 'c'
    db _lexer4D - _lexer4LUT ; 'd'
    db 255 ; 'e'
    db 255 ; 'f'
    db 255 ; 'g'
    db _lexer4H - _lexer4LUT ; 'h'
    db _lexer4I - _lexer4LUT ; 'i'
    db 255 ; 'j'
    db 255 ; 'k'
    db _lexer4L - _lexer4LUT ; 'l'
    db 255 ; 'm'
    db 255 ; 'n'
    db _lexer4O - _lexer4LUT ; 'o'
    db _lexer4P - _lexer4LUT ; 'p'
    db 255 ; 'q'
    db _lexer4R - _lexer4LUT ; 'r'

_lexer4LUT:
_lexer4Suffix:
    db "Nsis", typeModifier ; N instead of . because it broke since we correct cases
    db "Nsil", typeModifier
    db "Nlis", typeModifier
    db "Nlil", typeModifier

_lexer4C:
    db "call", typeInstruction
    db "cpir", typeInstruction
    db "cpdr", typeInstruction

_lexer4D:
    db "djnz", typeInstruction

_lexer4H:
    db "halt", typeInstruction

_lexer4I:
    db "indr", typeInstruction
    db "ind2", typeInstruction
    db "indm", typeInstruction
    db "ini2", typeInstruction
    db "inim", typeInstruction

_lexer4L:
    db "ldir", typeInstruction
    db "lddr", typeInstruction

_lexer4O:
    db "otdm", typeInstruction
    db "otim", typeInstruction
    db "out0", typeInstruction
    db "outd", typeInstruction
    db "outi", typeInstruction

_lexer4P:
    db "push", typeInstruction

_lexer4R:
    db "reti", typeInstruction
    db "retn", typeInstruction
    db "rlca", typeInstruction
    db "rrca", typeInstruction

_lexer3AlphaLUT:
    db _lexer3A - _lexer3LUT ; 'a'
    db _lexer3B - _lexer3LUT ; 'b'
    db _lexer3C - _lexer3LUT ; 'c'
    db _lexer3D - _lexer3LUT ; 'd'
    db _lexer3E - _lexer3LUT ; 'e'
    db 255 ; 'f'
    db 255 ; 'g'
    db 255 ; 'h'
    db _lexer3I - _lexer3LUT ; 'i'
    db 255 ; 'j'
    db 255 ; 'k'
    db _lexer3L - _lexer3LUT ; 'l'
    db _lexer3M - _lexer3LUT ; 'm'
    db _lexer3N - _lexer3LUT ; 'n'
    db _lexer3O - _lexer3LUT ; 'o'
    db _lexer3P - _lexer3LUT ; 'p'
    db 255 ; 'q'
    db _lexer3R - _lexer3LUT ; 'r'
    db _lexer3S - _lexer3LUT ; 's'
    db _lexer3T - _lexer3LUT ; 't'
    db 255 ; 'u'
    db 255 ; 'v'
    db 255 ; 'w'
    db _lexer3X - _lexer3LUT ; 'x'

_lexer3LUT:
_lexer3A:
    db "add", typeInstruction
    db "and", typeInstruction
    db "adc", typeInstruction
    db "af\'", typeRegister

_lexer3B:
    db "bit", typeInstruction

_lexer3C:
    db "cpi", typeInstruction
    db "cpd", typeInstruction
    db "ccf", typeInstruction
    db "cpl", typeInstruction

_lexer3D:
    db "dec", typeInstruction
    db "daa", typeInstruction

_lexer3E:
    db "exx", typeInstruction

_lexer3I:
    db "inc", typeInstruction
    db "ixh", typeRegister
    db "ixl", typeRegister
    db "iyh", typeRegister
    db "iyl", typeRegister
    db "in0", typeInstruction
    db "ind", typeInstruction
    db "ini", typeInstruction

_lexer3L:
    db "ldi", typeInstruction
    db "ldd", typeInstruction
    db "lea", typeInstruction

_lexer3M:
    db "mlt", typeInstruction

_lexer3N:
    db "neg", typeInstruction
    db "nop", typeInstruction

_lexer3O:
    db "out", typeInstruction

_lexer3P:
    db "pop", typeInstruction
    db "pea", typeInstruction

_lexer3R:
    db "ret", typeInstruction
    db "res", typeInstruction
    db "rla", typeInstruction
    db "rlc", typeInstruction
    db "rld", typeInstruction
    db "rra", typeInstruction
    db "rrc", typeInstruction
    db "rrd", typeInstruction
    db "rst", typeInstruction

_lexer3S:
    db "sbc", typeInstruction
    db "set", typeInstruction
    db "sub", typeInstruction
    db "sla", typeInstruction
    db "sll", typeInstruction
    db "sra", typeInstruction
    db "srl", typeInstruction
    db "scf", typeInstruction
    db "slp", typeInstruction

_lexer3T:
    db "tst", typeInstruction

_lexer3X:
    db "xor", typeInstruction

_lexer2AlphaLUT:
    db _lexer2A - _lexer2LUT ; 'a'
    db _lexer2B - _lexer2LUT ; 'b'
    db _lexer2C - _lexer2LUT ; 'c'
    db _lexer2D - _lexer2LUT ; 'd'
    db _lexer2E - _lexer2LUT ; 'e'
    db 255 ; 'f'
    db 255 ; 'g'
    db _lexer2H - _lexer2LUT ; 'h'
    db _lexer2I - _lexer2LUT ; 'i'
    db _lexer2J - _lexer2LUT ; 'j'
    db 255 ; 'k'
    db _lexer2L - _lexer2LUT ; 'l'
    db _lexer2M - _lexer2LUT ; 'm'
    db _lexer2N - _lexer2LUT ; 'n'
    db _lexer2O - _lexer2LUT ; 'o'
    db _lexer2P - _lexer2LUT ; 'p'
    db 255 ; 'q'
    db _lexer2R - _lexer2LUT ; 'r'
    db _lexer2S - _lexer2LUT ; 's'

_lexer2LUT:
_lexer2A:
    db "af", typeRegister

_lexer2B:
    db "bc", typeRegister

_lexer2C:
    db "cp", typeInstruction

_lexer2D:
    db "db", typeInstruction
    db "dw", typeInstruction
    db "dl", typeInstruction
    db "dd", typeInstruction
    db "de", typeRegister
    db "di", typeInstruction

_lexer2E:
    db "ei", typeInstruction
    db "ex", typeInstruction

_lexer2H:
    db "hl", typeRegister

_lexer2I:
    db "ix", typeRegister
    db "iy", typeRegister
    db "in", typeInstruction
    db "im", typeInstruction

_lexer2J:
    db "jp", typeInstruction
    db "jr", typeInstruction

_lexer2L:
    db "ld", typeInstruction

_lexer2M:
    db "mb", typeRegister

_lexer2N:
    db "nz", typeCondition
    db "nc", typeCondition

_lexer2O:
    db "or", typeInstruction

_lexer2P:
    db "pe", typeCondition
    db "po", typeCondition

_lexer2R:
    db "rb", typeInstruction
    db "rw", typeInstruction
    db "rl", typeInstruction
    db "rd", typeInstruction
    db "rr", typeInstruction

_lexer2S:
    db "sp", typeRegister

_lexer1LUT:
    db typeRegister ; 'a'
    db typeRegister ; 'b'
    db typeRegister ; 'c'
    db typeRegister ; 'd'
    db typeRegister ; 'e'
    db typeRegister ; 'f'
    db 0 ; 'g'
    db typeRegister ; 'h'
    db typeRegister ; 'i'
    db 0 ; 'j'
    db 0 ; 'k'
    db typeRegister ; 'l'
    db typeCondition ; 'm'
    db 0 ; 'n'
    db 0 ; 'o'
    db typeCondition ; 'p'
    db 0 ; 'q'
    db typeRegister ; 'r'
    db 0 ; 's'
    db 0 ; 't'
    db 0 ; 'u'
    db 0 ; 'v'
    db 0 ; 'w'
    db 0 ; 'x'
    db 0 ; 'y'
    db typeCondition ; 'z'
