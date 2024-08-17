;--------------------------------------
;
; eZ80 Studio Source Code - opcodes.asm
; By RoccoLox Programs and TIny_Hacker
; Copyright 2022 - 2024
; License: GPL-3.0
;
;--------------------------------------

;----------------------------------------------
; List of eZ80 Opcodes.
; Source: https://www.zilog.com/docs/um0077.pdf
;
; Format:
; db size, opcode, name (null-terminated)
;
; For arguments:
; '#' = number
;----------------------------------------------

;--------------------------
; Opcode Map - First Opcode
;--------------------------

    assume adl=1

    section .rodata

    public _asm_opcodes_Table
    public _asm_opcodes_AfterCB
    public _asm_opcodes_AfterDD
    public _asm_opcodes_AfterED
    public _asm_opcodes_AfterFD
    public _asm_opcodes_AfterDDCB
    public _asm_opcodes_AfterFDCB
    public _asm_opcodes_TableEnd

_asm_opcodes_Table:

db 1
db $00
db "nop", 0

db 4
db $01, $00, $00, $00
db "ld bc,#", 0

db 1
db $02
db "ld (bc),a", 0

db 1
db $03
db "inc bc", 0

db 1
db $04
db "inc b", 0

db 1
db $05
db "dec b", 0

db 2
db $06, $00
db "ld b,#", 0

db 1
db $07
db "rlca", 0

db 1
db $08
db "ex af,af'", 0

db 1
db $09
db "add hl,bc", 0

db 1
db $0A
db "ld a,(bc)", 0

db 1
db $0B
db "dec bc", 0

db 1
db $0C
db "inc c", 0

db 1
db $0D
db "dec c", 0

db 2
db $0E, $00
db "ld c,#", 0

db 1
db $0F
db "rrca", 0

db 2
db $10, $00
db "djnz #", 0

db 4
db $11, $00, $00, $00
db "ld de,#", 0

db 1
db $12
db "ld (de),a", 0

db 1
db $13
db "inc de", 0

db 1
db $14
db "inc d", 0

db 1
db $15
db "dec d", 0

db 2
db $16, $00
db "ld d,#", 0

db 1
db $17
db "rla", 0

db 2
db $18, $00
db "jr #", 0

db 1
db $19
db "add hl,de", 0

db 1
db $1A
db "ld a,(de)", 0

db 1
db $1B
db "dec de", 0

db 1
db $1C
db "inc e", 0

db 1
db $1D
db "dec e", 0

db 2
db $1E, $00
db "ld e,#", 0

db 1
db $1F
db "rra", 0

db 2
db $20, $00
db "jr nz,#", 0

db 4
db $21, $00, $00, $00
db "ld hl,#", 0

db 4
db $22, $00, $00, $00
db "ld (#),hl", 0

db 1
db $23
db "inc hl", 0

db 1
db $24
db "inc h", 0

db 1
db $25
db "dec h", 0

db 2
db $26, $00
db "ld h,#", 0

db 1
db $27
db "daa", 0

db 2
db $28, $00
db "jr z,#", 0

db 1
db $29
db "add hl,hl", 0

db 4
db $2A, $00, $00, $00
db "ld hl,(#)", 0

db 1
db $2B
db "dec hl", 0

db 1
db $2C
db "inc l", 0

db 1
db $2D
db "dec l", 0

db 2
db $2E, $00
db "ld l,#", 0

db 1
db $2F
db "cpl", 0

db 2
db $30, $00 
db "jr nc,#", 0

db 4
db $31, $00, $00, $00
db "ld sp,#", 0

db 4
db $32, $00, $00, $00
db "ld (#),a", 0

db 1
db $33
db "inc sp", 0

db 1
db $34
db "inc (hl)", 0

db 1
db $35
db "dec (hl)", 0

db 2
db $36, $00
db "ld (hl),#", 0

db 1
db $37
db "scf", 0

db 2
db $38, $00
db "jr c,#", 0

db 1
db $39
db "add hl,sp", 0

db 4
db $3A, $00, $00, $00
db "ld a,(#)", 0

db 1
db $3B
db "dec sp", 0

db 1
db $3C
db "inc a", 0

db 1
db $3D
db "dec a", 0

db 2
db $3E, $00
db "ld a,#", 0

db 1
db $3F
db "ccf", 0

; db 1
; db $40
; db ".sis", 0

db 1
db $41
db "ld b,c", 0

db 1
db $42
db "ld b,d", 0

db 1
db $43
db "ld b,e", 0

db 1
db $44
db "ld b,h", 0

db 1
db $45
db "ld b,l", 0

db 1
db $46
db "ld b,(hl)", 0

db 1
db $47
db "ld b,a", 0

db 1
db $48
db "ld c,b", 0

; db 1
; db $49
; db ".lis", 0

db 1
db $4A
db "ld c,d", 0

db 1
db $4B
db "ld c,e", 0

db 1
db $4C
db "ld c,h", 0

db 1
db $4D
db "ld c,l", 0

db 1
db $4E
db "ld c,(hl)", 0

db 1
db $4F
db "ld c,a", 0

db 1
db $50
db "ld d,b", 0

db 1
db $51
db "ld d,c", 0

; db 1
; db $52
; db ".sil", 0

db 1
db $53
db "ld d,e", 0

db 1
db $54
db "ld d,h", 0

db 1
db $55
db "ld d,l", 0

db 1
db $56
db "ld d,(hl)", 0

db 1
db $57
db "ld d,a", 0

db 1
db $58
db "ld e,b", 0

db 1
db $59
db "ld e,c", 0

db 1
db $5A
db "ld e,d", 0

; db 1
; db $5B
; db ".lil", 0

db 1
db $5C
db "ld e,h", 0

db 1
db $5D
db "ld e,l", 0

db 1
db $5E
db "ld e,(hl)", 0

db 1
db $5F
db "ld e,a", 0

db 1
db $60
db "ld h,b", 0

db 1
db $61
db "ld h,c", 0

db 1
db $62
db "ld h,d", 0

db 1
db $63
db "ld h,e", 0

db 1
db $64
db "ld h,h", 0

db 1
db $65
db "ld h,l", 0

db 1
db $66
db "ld h,(hl)", 0

db 1
db $67
db "ld h,a", 0

db 1
db $68
db "ld l,b", 0

db 1
db $69
db "ld l,c", 0

db 1
db $6A
db "ld l,d", 0

db 1
db $6B
db "ld l,e", 0

db 1
db $6C
db "ld l,h", 0

db 1
db $6D
db "ld l,l", 0

db 1
db $6E
db "ld l,(hl)", 0

db 1
db $6F
db "ld l,a", 0

db 1
db $70
db "ld (hl),b", 0

db 1
db $71
db "ld (hl),c", 0

db 1
db $72
db "ld (hl),d", 0

db 1
db $73
db "ld (hl),e", 0

db 1
db $74
db "ld (hl),h", 0

db 1
db $75
db "ld (hl),l", 0

db 1
db $76
db "halt", 0

db 1
db $77
db "ld (hl),a", 0

db 1
db $78
db "ld a,b", 0

db 1
db $79
db "ld a,c", 0

db 1
db $7A
db "ld a,d", 0

db 1
db $7B
db "ld a,e", 0

db 1
db $7C
db "ld a,h", 0

db 1
db $7D
db "ld a,l", 0

db 1
db $7E
db "ld a,(hl)", 0

db 1
db $7F
db "ld a,a", 0

db 1
db $80
db "add a,b", 0

db 1
db $81
db "add a,c", 0

db 1
db $82
db "add a,d", 0

db 1
db $83
db "add a,e", 0

db 1
db $84
db "add a,h", 0

db 1
db $85
db "add a,l", 0

db 1
db $86
db "add a,(hl)", 0

db 1
db $87
db "add a,a", 0

db 1
db $88
db "adc a,b", 0

db 1
db $89
db "adc a,c", 0

db 1
db $8A
db "adc a,d", 0

db 1 
db $8B
db "adc a,e", 0

db 1
db $8C
db "adc a,h", 0

db 1
db $8D
db "adc a,l", 0

db 1
db $8E
db "adc a,(hl)", 0

db 1
db $8F
db "adc a,a", 0

db 1
db $90
db "sub a,b",0

db 1
db $91
db "sub a,c", 0

db 1
db $92
db "sub a,d", 0

db 1
db $93
db "sub a,e", 0

db 1
db $94
db "sub a,h", 0

db 1
db $95
db "sub a,l", 0

db 1
db $96
db "sub a,(hl)", 0

db 1
db $97
db "sub a,a", 0

db 1
db $98
db "sbc a,b", 0

db 1
db $99
db "sbc a,c", 0

db 1
db $9A
db "sbc a,d", 0

db 1
db $9B
db "sbc a,e", 0

db 1
db $9C
db "sbc a,h", 0

db 1
db $9D
db "sbc a,l", 0

db 1
db $9E
db "sbc a,(hl)", 0

db 1
db $9F
db "sbc a,a", 0

db 1
db $A0
db "and a,b", 0

db 1
db $A1
db "and a,c", 0

db 1
db $A2
db "and a,d", 0

db 1
db $A3
db "and a,e", 0

db 1
db $A4
db "and a,h", 0

db 1
db $A5
db "and a,l", 0

db 1
db $A6
db "and a,(hl)", 0

db 1
db $A7
db "and a,a", 0

db 1
db $A8
db "xor a,b", 0

db 1
db $A9
db "xor a,c", 0

db 1
db $AA
db "xor a,d", 0

db 1
db $AB
db "xor a,e", 0

db 1
db $AC
db "xor a,h", 0

db 1
db $AD
db "xor a,l", 0

db 1
db $AE
db "xor a,(hl)", 0

db 1
db $AF
db "xor a,a", 0

db 1
db $B0
db "or a,b", 0

db 1
db $B1
db "or a,c", 0

db 1
db $B2
db "or a,d", 0

db 1
db $B3
db "or a,e", 0

db 1
db $B4
db "or a,h", 0

db 1
db $B5
db "or a,l", 0

db 1
db $B6
db "or a,(hl)", 0

db 1
db $B7
db "or a,a", 0

db 1
db $B8
db "cp a,b", 0

db 1
db $B9
db "cp a,c", 0

db 1
db $BA
db "cp a,d", 0

db 1
db $BB
db "cp a,e", 0

db 1
db $BC
db "cp a,h", 0

db 1
db $BD
db "cp a,l", 0

db 1
db $BE
db "cp a,(hl)", 0

db 1
db $BF
db "cp a,a", 0

db 1
db $C0
db "ret nz", 0

db 1
db $C1
db "pop bc", 0

db 4
db $C2, $00, $00, $00
db "jp nz,#", 0

db 4
db $C3, $00, $00, $00
db "jp #", 0

db 4
db $C4, $00, $00, $00
db "call nz,#", 0

db 1
db $C5
db "push bc", 0

db 2
db $C6, $00
db "add a,#", 0

db 1
db $C7
db "rst 00", 0

db 1
db $C8
db "ret z", 0

db 1
db $C9
db "ret", 0

db 4
db $CA, $00, $00, $00
db "jp z,#", 0

; db 1
; db $CB
; bit opcodes

db 4
db $CC, $00, $00, $00
db "call z,#", 0

db 4
db $CD, $00, $00, $00
db "call #", 0

db 2
db $CE, $00
db "adc a,#", 0

db 1
db $CF
db "rst 08", 0

db 1
db $D0
db "ret nc", 0

db 1
db $D1
db "pop de", 0

db 4
db $D2, $00, $00, $00
db "jp nc,#", 0

db 2
db $D3, $00
db "out (#),a", 0

db 4
db $D4, $00, $00, $00
db "call nc,#", 0

db 1
db $D5
db "push de", 0

db 2
db $D6, $00
db "sub a,#", 0

db 1
db $D7
db "rst 10", 0

db 1
db $D8
db "ret c", 0

db 1
db $D9
db "exx", 0

db 4
db $DA, $00, $00, $00
db "jp c,#", 0

db 2
db $DB, $00
db "in a,(#)", 0

db 4
db $DC, $00, $00, $00
db "call c,#", 0

; db 1
; db $DD
; ix opcodes

db 2
db $DE, $00
db "sbc a,#", 0

db 1
db $DF
db "rst 18", 0

db 1
db $E0
db "ret po", 0

db 1
db $E1
db "pop hl", 0

db 4
db $E2, $00, $00, $00
db "jp po,#", 0

db 1
db $E3
db "ex (sp),hl", 0

db 4
db $E4, $00, $00, $00
db "call po,#", 0

db 1
db $E5
db "push hl", 0

db 2
db $E6, $00
db "and a,#", 0

db 1
db $E7
db "rst 20", 0

db 1
db $E8
db "ret pe", 0

db 1
db $E9
db "jp (hl)", 0

db 4
db $EA, $00, $00, $00
db "jp pe,#", 0

db 1
db $EB
db "ex de,hl", 0

db 4
db $EC, $00, $00, $00
db "call pe,#", 0

; db 1
; db $ED
; port opcodes

db 2
db $EE, $00
db "xor a,#", 0

db 1
db $EF
db "rst 28", 0

db 1
db $F0
db "ret p", 0

db 1
db $F1
db "pop af", 0

db 4
db $F2, $00, $00, $00
db "jp p,#", 0

db 1
db $F3
db "di", 0

db 4
db $F4, $00, $00, $00
db "call p,#", 0

db 1
db $F5
db "push af", 0

db 2
db $F6, $00
db "or a,#", 0

db 1
db $F7
db "rst 30", 0

db 1
db $F8
db "ret m", 0

db 1
db $F9
db "ld sp,hl", 0

db 4
db $FA, $00, $00, $00
db "jp m,#", 0

db 1
db $FB
db "ei", 0

db 4
db $FC, $00, $00, $00
db "call m,#", 0

; db 1
; db $FD
; iy opcodes

db 2
db $FE, $00
db "cp a,#", 0

db 1
db $FF
db "rst 38", 0

;---------------------------------------
; Opcode Map - Second Opcode (after $CB)
;---------------------------------------

_asm_opcodes_AfterCB:

db 1
db $00
db "rlc b", 0

db 1
db $01
db "rlc c", 0

db 1
db $02
db "rlc d", 0

db 1
db $03
db "rlc e", 0

db 1
db $04
db "rlc h", 0

db 1
db $05
db "rlc l", 0

db 1
db $06
db "rlc (hl)", 0

db 1
db $07
db "rlc a", 0

db 1
db $08
db "rrc b", 0

db 1
db $09
db "rrc c", 0

db 1
db $0A
db "rrc d", 0

db 1
db $0B
db "rrc e", 0

db 1
db $0C
db "rrc h", 0

db 1
db $0D
db "rrc l", 0

db 1
db $0E
db "rrc (hl)", 0

db 1
db $0F
db "rrc a", 0

db 1
db $10
db "rl b", 0

db 1
db $11
db "rl c", 0

db 1
db $12
db "rl d", 0

db 1
db $13
db "rl e", 0

db 1
db $14
db "rl h", 0

db 1
db $15
db "rl l", 0

db 1
db $16
db "rl (hl)", 0

db 1
db $17
db "rl a", 0

db 1
db $18
db "rr b", 0

db 1
db $19
db "rr c", 0

db 1
db $1A
db "rr d", 0

db 1
db $1B
db "rr e", 0

db 1
db $1C
db "rr h", 0

db 1
db $1D
db "rr l", 0

db 1
db $1E
db "rr (hl)", 0

db 1
db $1F
db "rr a", 0

db 1
db $20
db "sla b", 0

db 1
db $21
db "sla c", 0

db 1
db $22
db "sla d", 0

db 1
db $23
db "sla e", 0

db 1
db $24
db "sla h", 0

db 1
db $25
db "sla l", 0

db 1
db $26
db "sla (hl)", 0

db 1
db $27
db "sla a", 0

db 1
db $28
db "sra b", 0

db 1
db $29
db "sra c", 0

db 1
db $2A
db "sra d", 0

db 1
db $2B
db "sra e", 0

db 1
db $2C
db "sra h", 0

db 1
db $2D
db "sra l", 0

db 1
db $2E
db "sra (hl)", 0

db 1
db $2F
db "sra a", 0

db 1
db $38
db "srl b", 0

db 1
db $39
db "srl c", 0

db 1
db $3A
db "srl d", 0

db 1
db $3B
db "srl e", 0

db 1
db $3C
db "srl h", 0

db 1
db $3D
db "srl l", 0

db 1
db $3E
db "srl (hl)", 0

db 1
db $3F
db "srl a", 0

db 1
db $40
db "bit #,b", 0

db 1
db $41
db "bit #,c", 0

db 1
db $42
db "bit #,d", 0

db 1
db $43
db "bit #,e", 0

db 1
db $44
db "bit #,h", 0

db 1
db $45
db "bit #,l", 0

db 1
db $46
db "bit #,(hl)", 0

db 1
db $47
db "bit #,a", 0

db 1
db $80
db "res #,b", 0

db 1
db $81
db "res #,c", 0

db 1
db $82
db "res #,d", 0

db 1
db $83
db "res #,e", 0

db 1
db $84
db "res #,h", 0

db 1
db $85
db "res #,l", 0

db 1
db $86
db "res #,(hl)", 0

db 1
db $87
db "res #,a", 0

db 1
db $C0
db "set #,b", 0

db 1
db $C1
db "set #,c", 0

db 1
db $C2
db "set #,d", 0

db 1
db $C3
db "set #,e", 0

db 1
db $C4
db "set #,h", 0

db 1
db $C5
db "set #,l", 0

db 1
db $C6
db "set #,(hl)", 0

db 1
db $C7
db "set #,a", 0

;---------------------------------------
; Opcode Map - Second Opcode (after $DD)
;---------------------------------------

_asm_opcodes_AfterDD:

db 2
db $07, $00
db "ld bc,(ix#)", 0

db 1
db $09
db "add ix,bc", 0

db 2
db $0F, $00
db "ld (ix#),bc", 0

db 2
db $17, $00
db "ld de,(ix#)", 0

db 1
db $19
db "add ix,de", 0

db 2
db $1F, $00
db "ld (ix#),de", 0

db 4
db $21, $00, $00, $00
db "ld ix,#", 0

db 4
db $22, $00, $00, $00
db "ld (#),ix", 0

db 1
db $23
db "inc ix", 0

db 1
db $24
db "inc ixh", 0

db 1
db $25
db "dec ixh", 0

db 2
db $26, $00
db "ld ixh,#", 0

db 2
db $27, $00
db "ld hl,(ix#)", 0

db 1
db $29
db "add ix,ix", 0

db 4
db $2A, $00, $00, $00
db "ld ix,(#)", 0

db 1
db $2B
db "dec ix", 0

db 1
db $2C
db "inc ixl", 0

db 1
db $2D
db "dec ixl", 0

db 2
db $2E, $00
db "ld ixl,#", 0

db 2
db $2F, $00
db "ld (ix#),hl", 0

db 2
db $31, $00
db "ld iy,(ix#)", 0

db 2
db $34, $00
db "inc (ix#)", 0

db 2
db $35, $00
db "dec (ix#)", 0

db 3
db $36, $00, $00
db "ld (ix#),#", 0

db 2
db $37, $00
db "ld ix,(ix#)", 0

db 1
db $39
db "add ix,sp", 0

db 2
db $3E, $00
db "ld (ix#),iy", 0

db 2
db $3F, $00
db "ld (ix#),ix", 0

db 1
db $44
db "ld b,ixh", 0

db 1
db $45
db "ld b,ixl", 0

db 2
db $46, $00
db "ld b,(ix#)", 0

db 1
db $4C
db "ld c,ixh", 0

db 1
db $4D
db "ld c,ixl", 0

db 2
db $4E, $00
db "ld c,(ix#)", 0

db 1
db $54
db "ld d,ixh", 0

db 1
db $55
db "ld d,ixl", 0

db 2
db $56, $00
db "ld d,(ix#)", 0

db 1
db $5C
db "ld e,ixh", 0

db 1
db $5D
db "ld e,ixl", 0

db 2
db $5E, $00
db "ld e,(ix#)", 0

db 1
db $60
db "ld ixh,b", 0

db 1
db $61
db "ld ixh,c", 0

db 1
db $62
db "ld ixh,d", 0

db 1
db $63
db "ld ixh,e", 0

db 1
db $64
db "ld ixh,ixh", 0

db 1
db $65
db "ld ixh,ixl", 0

db 2
db $66, $00
db "ld h,(ix#)", 0

db 1
db $67
db "ld ixh,a", 0

db 1
db $68
db "ld ixl,b", 0

db 1
db $69
db "ld ixl,c", 0

db 1
db $6A
db "ld ixl,d", 0

db 1
db $6B
db "ld ixl,e", 0

db 1
db $6C
db "ld ixl,ixh", 0

db 1
db $6D
db "ld ixl,ixl", 0

db 2
db $6E, $00
db "ld l,(ix#)", 0

db 1
db $6F
db "ld ixl,a", 0

db 2
db $70, $00
db "ld (ix#),b", 0

db 2
db $71, $00
db "ld (ix#),c", 0

db 2
db $72, $00
db "ld (ix#),d", 0

db 2
db $73, $00
db "ld (ix#),e", 0

db 2
db $74, $00
db "ld (ix#),h", 0

db 2
db $75, $00
db "ld (ix#),l", 0

db 2
db $77, $00
db "ld (ix#),a", 0

db 1
db $7C
db "ld a,ixh", 0

db 1
db $7D
db "ld a,ixl", 0

db 2
db $7E, $00
db "ld a,(ix#)", 0

db 1
db $84
db "add a,ixh", 0

db 1
db $85
db "add a,ixl", 0

db 2
db $86, $00
db "add a,(ix#)", 0

db 1
db $8C
db "adc a,ixh", 0

db 1
db $8D
db "adc a,ixl", 0

db 2
db $8E, $00
db "adc a,(ix#)", 0

db 1
db $94
db "sub a,ixh", 0

db 1
db $95
db "sub a,ixl", 0

db 2
db $96, $00
db "sub a,(ix#)", 0

db 1
db $9C
db "sbc a,ixh", 0

db 1
db $9D
db "sbc a,ixl", 0

db 2
db $9E, $00
db "sbc a,(ix#)", 0

db 1
db $A4
db "and a,ixh", 0

db 1
db $A5
db "and a,ixl", 0

db 2
db $A6, $00
db "and a,(ix#)", 0

db 1
db $AC
db "xor a,ixh", 0

db 1
db $AD
db "xor a,ixl", 0

db 2
db $AE, $00
db "xor a,(ix#)", 0

db 1
db $B4
db "or a,ixh", 0

db 1
db $B5
db "or a,ixl", 0

db 2
db $B6, $00
db "or a,(ix#)", 0

db 1
db $BC
db "cp a,ixh", 0

db 1
db $BD
db "cp a,ixl", 0

db 2
db $BE, $00
db "cp a,(ix#)", 0

db 1
db $E1
db "pop ix", 0

db 1
db $E3
db "ex (sp),ix", 0

db 1
db $E5
db "push ix", 0

db 1
db $E9
db "jp (ix)", 0

db 1
db $F9
db "ld sp,ix", 0

;---------------------------------------
; Opcode Map - Second Opcode (after $ED)
;---------------------------------------

_asm_opcodes_AfterED:

db 2
db $00, $00
db "in0,(#)", 0

db 2
db $01, $00
db "out0,(#)", 0

db 2
db $02, $00
db "lea bc,ix#", 0

db 2
db $03, $00
db "lea bc,iy#", 0

db 1
db $04
db "tst a,b", 0

db 1
db $07
db "ld bc,(hl)", 0

db 2
db $08, $00
db "in0 c,(#)", 0

db 2
db $09, $00
db "out0 (#),c", 0

db 1
db $0C
db "tst a,c", 0

db 1
db $0F
db "ld (hl),bc", 0

db 2
db $10, $00
db "in0 d,(#)", 0

db 2
db $11, $00
db "out0 (#),d", 0

db 2
db $12, $00
db "lea de,ix#", 0

db 2
db $13, $00
db "lea de,iy#", 0

db 1
db $14
db "tst a,d", 0

db 1
db $17
db "ld de,(hl)", 0

db 2
db $18, $00
db "in0 e,(#)", 0

db 2
db $19, $00
db "out0 (#),e", 0

db 1
db $1C
db "tst a,e", 0

db 1
db $1F
db "ld (hl),de", 0

db 2
db $20, $00
db "in0 h,(#)", 0

db 2
db $21, $00
db "out0 (#),h", 0

db 2
db $22, $00
db "lea hl,ix#", 0

db 2
db $23, $00
db "lea hl,iy#", 0

db 1
db $24
db "tst a,h", 0

db 1
db $27
db "ld hl,(hl)", 0

db 2
db $28, $00
db "in0 l,(#)", 0

db 2
db $29, $00
db "out0 (#),l", 0

db 1
db $2C
db "tst a,l", 0

db 1
db $2F
db "ld (hl),hl", 0

db 1
db $31
db "ld iy,(hl)", 0

db 2
db $32, $00
db "ld ix,ix#", 0

db 2
db $33, $00
db "ld iy,iy#", 0

db 1
db $34
db "tst a,(hl)", 0

db 1
db $37
db "ld ix,(hl)", 0

db 2
db $38, $00
db "in0 a,(#)", 0

db 2
db $39, $00
db "out0 (#),a", 0

db 1
db $3C
db "tst a,a", 0

db 1
db $3E
db "ld (hl),iy", 0

db 1
db $3F
db "ld (hl),ix", 0

db 1
db $40
db "in b,(bc)", 0

db 1
db $41
db "out (bc),b", 0

db 1
db $42
db "sbc hl,bc", 0

db 4
db $43, $00, $00, $00
db "ld (#),bc", 0

db 1
db $44
db "neg", 0

db 1
db $45
db "retn", 0

db 1
db $46
db "im 0", 0

db 1
db $47
db "ld i,a", 0

db 1
db $48
db "in c,(bc)", 0

db 1
db $49
db "out (bc),c", 0

db 1
db $4A
db "adc hl,bc", 0

db 4
db $4B, $00, $00, $00
db "ld bc,(#)", 0

db 1
db $4C
db "mlt bc", 0

db 1
db $4D
db "reti", 0

db 1
db $4F
db "ld r,a", 0

db 1
db $50
db "in d,(bc)", 0

db 1
db $51
db "out (bc),d", 0

db 1
db $52
db "sbc hl,de", 0

db 4
db $53, $00, $00, $00
db "ld (#),de"

db 2
db $54, $00
db "lea ix,iy#", 0

db 2
db $55, $00
db "lea iy,ix#", 0

db 1
db $56
db "im 1", 0

db 1
db $57
db "ld a,i", 0

db 1
db $58
db "in e,(bc)", 0

db 1
db $59
db "out (bc),e", 0

db 1
db $5A
db "adc hl,de", 0

db 4
db $5B, $00, $00, $00
db "ld de,(#)", 0

db 1
db $5C
db "mlt de", 0

db 1
db $5E
db "im 2", 0

db 1
db $5F
db "ld a,r", 0

db 1
db $60
db "in h,(bc)", 0

db 1
db $61
db "out (bc),h", 0

db 1
db $62
db "sbc hl,hl", 0

db 4
db $63, $00, $00, $00
db "ld (#),hl", 0

db 2
db $64, $00
db "tst a,#", 0

db 2
db $65, $00
db "pea ix#", 0

db 2
db $66, $00
db "pea iy#", 0

db 1
db $67
db "rrd", 0

db 1
db $68
db "in l,(bc)", 0

db 1
db $69
db "out (bc),l", 0

db 1
db $6A
db "adc hl,hl", 0

db 4
db $6B, $00, $00
db "ld hl,(#)", 0

db 1
db $6C
db "mlt hl", 0

db 1
db $6D
db "ld mb,a", 0

db 1
db $6E
db "ld a,mb", 0

db 1
db $6F
db "rld", 0

db 1
db $72
db "sbc hl,sp", 0

db 4
db $73, $00, $00, $00
db "ld (#),sp", 0

db 2
db $74, $00
db "tstio #", 0

db 1
db $76
db "slp", 0

db 1
db $78
db "in a,(bc)", 0

db 1
db $79
db "out (bc),a", 0

db 1
db $7A
db "adc hl,sp", 0

db 4
db $7B, $00, $00, $00
db "ld sp,(#)", 0

db 1
db $7C
db "mlt sp", 0

db 1
db $7D
db "stmix", 0

db 1
db $7E
db "rsmix", 0

db 1
db $82
db "inim", 0

db 1
db $82
db "otim", 0

db 1
db $83
db "ini2", 0

db 1
db $8A
db "indm", 0

db 1
db $8B
db "otdm", 0

db 1
db $8C
db "ind2", 0

db 1
db $92
db "inimr", 0

db 1
db $93
db "otimr", 0

db 1
db $94 
db "ini2r", 0

db 1
db $9A
db "indmr", 0

db 1
db $9B
db "otdmr", 0

db 1
db $9C
db "ind2r", 0

db 1
db $A0
db "ldi", 0

db 1
db $A1
db "cpi", 0

db 1
db $A2
db "ini", 0

db 1
db $A3
db "outi", 0

db 1
db $A4
db "outi2", 0

db 1
db $A8
db "ldd", 0

db 1
db $A9
db "cpd", 0

db 1
db $AA
db "ind", 0

db 1
db $AB
db "outd", 0

db 1
db $AC
db "outd2", 0

db 1
db $B0
db "ldir", 0

db 1
db $B1
db "cpir", 0

db 1
db $B2
db "inir", 0

db 1
db $B3
db "otir", 0

db 1
db $B4
db "oti2r", 0

db 1
db $B8
db "lddr", 0

db 1
db $B9
db "cpdr", 0

db 1
db $BA
db "indr", 0

db 1
db $BB
db "otdr", 0

db 1
db $BC
db "otd2r", 0

db 1
db $C2
db "inirx", 0

db 1
db $C3
db "otirx", 0

db 1
db $C7
db "ld i,hl", 0

db 1
db $CA
db "indrx", 0

db 1
db $CB
db "otdrx", 0

db 1
db $D7
db "ld hl,i", 0

;---------------------------------------
; Opcode Map - Second Opcode (after $FD)
;---------------------------------------

_asm_opcodes_AfterFD:

db 2
db $07, $00
db "ld bc,(iy#)", 0

db 1
db $09
db "add iy,bc", 0

db 2
db $0F, $00
db "ld (iy#),bc", 0

db 2
db $17, $00
db "ld de,(iy#)", 0

db 1
db $19
db "add iy,de", 0

db 2
db $1F, $00
db "ld (iy#),de", 0

db 4
db $21, $00, $00, $00
db "ld iy,#", 0

db 4
db $22, $00, $00, $00
db "ld (#),iy", 0

db 1
db $23
db "inc iy", 0

db 1
db $24
db "inc iyh", 0

db 1
db $25
db "dec iyh", 0

db 2
db $26, $00
db "ld iyh,#", 0

db 2
db $27, $00
db "ld hl,(iy#)", 0

db 1
db $29
db "add iy,iy", 0

db 4
db $2A, $00, $00, $00
db "ld iy,(#)", 0

db 1
db $2B
db "dec iy", 0

db 1
db $2C
db "inc iyl", 0

db 1
db $2D
db "dec iyl", 0

db 2
db $2E, $00
db "ld iyl,#", 0

db 2
db $2F, $00
db "ld (iy#),hl", 0

db 2
db $31, $00
db "ld ix,(iy#)", 0

db 2
db $34, $00
db "inc (iy#)", 0

db 2
db $35, $00
db "dec (iy#)", 0

db 3
db $36, $00, $00
db "ld (iy#),#", 0

db 2
db $37, $00
db "ld iy,(iy#)", 0

db 1
db $39
db "add iy,sp", 0

db 2
db $3E, $00
db "ld (iy#),ix", 0

db 2
db $3F, $00
db "ld (iy#),iy", 0

db 1
db $44
db "ld b,iyh", 0

db 1
db $45
db "ld b,iyl", 0

db 2
db $46, $00
db "ld b,(iy#)", 0

db 1
db $4C
db "ld c,iyh", 0

db 1
db $4D
db "ld c,iyl", 0

db 2
db $4E, $00
db "ld c,(iy#)", 0

db 1
db $54
db "ld d,iyh", 0

db 1
db $55
db "ld d,iyl", 0

db 2
db $56, $00
db "ld d,(iy#)", 0

db 1
db $5C
db "ld e,iyh", 0

db 1
db $5D
db "ld e,iyl", 0

db 2
db $5E, $00
db "ld e,(iy#)", 0

db 1
db $60
db "ld iyh,b", 0

db 1
db $61
db "ld iyh,c", 0

db 1
db $62
db "ld iyh,d", 0

db 1
db $63
db "ld iyh,e", 0

db 1
db $64
db "ld iyh,iyh", 0

db 1
db $65
db "ld iyh,iyl", 0

db 2
db $66, $00
db "ld h,(iy#)", 0

db 1
db $67
db "ld iyh,a", 0

db 1
db $68
db "ld iyl,b", 0

db 1
db $69
db "ld iyl,c", 0

db 1
db $6A
db "ld iyl,d", 0

db 1
db $6B
db "ld iyl,e", 0

db 1
db $6C
db "ld iyl,iyh", 0

db 1
db $6D
db "ld iyl,iyl", 0

db 2
db $6E, $00
db "ld l,(iy#)", 0

db 1
db $6F
db "ld iyl,a", 0

db 2
db $70, $00
db "ld (iy#),b", 0

db 2
db $71, $00
db "ld (iy#),c", 0

db 2
db $72, $00
db "ld (iy#),d", 0

db 2
db $73, $00
db "ld (iy#),e", 0

db 2
db $74, $00
db "ld (iy#),h", 0

db 2
db $75, $00
db "ld (iy#),l", 0

db 2
db $77, $00
db "ld (iy#),a", 0

db 1
db $7C
db "ld a,iyh", 0

db 1
db $7D
db "ld a,iyl", 0

db 2
db $7E, $00
db "ld a,(iy#)", 0

db 1
db $84
db "add a,iyh", 0

db 1
db $85
db "add a,iyl", 0

db 2
db $86, $00
db "add a,(iy#)", 0

db 1
db $8C
db "adc a,iyh", 0

db 1
db $8D
db "adc a,iyl", 0

db 2
db $8E, $00
db "adc a,(iy#)", 0

db 1
db $94
db "sub a,iyh", 0

db 1
db $95
db "sub a,iyl", 0

db 2
db $96, $00
db "sub a,(iy#)", 0

db 1
db $9C
db "sbc a,iyh", 0

db 1
db $9D
db "sbc a,iyl", 0

db 2
db $9E, $00
db "sbc a,(iy#)", 0

db 1
db $A4
db "and a,iyh", 0

db 1
db $A5
db "and a,iyl", 0

db 2
db $A6, $00
db "and a,(iy#)", 0

db 1
db $AC
db "xor a,iyh", 0

db 1
db $AD
db "xor a,iyl", 0

db 2
db $AE, $00
db "xor a,(iy#)", 0

db 1
db $B4
db "or a,iyh", 0

db 1
db $B5
db "or a,iyl", 0

db 2
db $B6, $00
db "or a,(iy#)", 0

db 1
db $BC
db "cp a,iyh", 0

db 1
db $BD
db "cp a,iyl", 0

db 2
db $BE, $00
db "cp a,(iy#)", 0

db 1
db $E1
db "pop iy", 0

db 1
db $E3
db "ex (sp),iy", 0

db 1
db $E5
db "push iy", 0

db 1
db $E9
db "jp (iy)", 0

db 1
db $F9
db "ld sp,iy", 0

;-------------------------------------------
; Opcode Map - Fourth Opcode (after $DDCB##)
;-------------------------------------------

_asm_opcodes_AfterDDCB:

db 1
db $06
db "rlc (ix#)", 0

db 1
db $0E
db "rrc (ix#)", 0

db 1
db $16
db "rl (ix#)", 0

db 1
db $1E
db "rr (ix#)", 0

db 1
db $26
db "sla (ix#)", 0

db 1
db $2E
db "sra (ix#)", 0

db 1
db $3E
db "srl (ix#)", 0

db 1
db $46
db "bit #,(ix#)", 0

db 1
db $86
db "res #,(ix#)", 0

db 1
db $C6
db "set #,(ix#)", 0

;-------------------------------------------
; Opcode Map - Fourth Opcode (after $FDCB##)
;-------------------------------------------

_asm_opcodes_AfterFDCB:

db 1
db $06
db "rlc (ix#)", 0

db 1
db $0E
db "rrc (ix#)", 0

db 1
db $16
db "rl (ix#)", 0

db 1
db $1E
db "rr (ix#)", 0

db 1
db $26
db "sla (ix#)", 0

db 1
db $2E
db "sra (ix#)", 0

db 1
db $3E
db "srl (ix#)", 0

db 1
db $46
db "bit #,(ix#)", 0

db 1
db $86
db "res #,(ix#)", 0

db 1
db $C6
db "set #,(ix#)", 0

_asm_opcodes_TableEnd:
