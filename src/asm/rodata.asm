;--------------------------------------
;
; eZ80 Studio Source Code - rodata.asm
; By RoccoLox Programs and TIny_Hacker
; Copyright 2022 - 2024
; License: GPL-3.0
;
;--------------------------------------

    assume adl=1

    section .rodata

include 'include/equates.inc'

    public _rodata_characters
    public _rodata_sizeOfCharsLUT

_rodata_characters:
    ; numbers
    db 10                      ; ENTER
    db '+-*/^', 0              ; + - × ÷ ^ undef
    db '-369)', 0, 0, 0        ; (-) 3 6 9 ) TAN VARS undef
    db '.258(', 0, 0, 0        ; . 2 5 8 ( COS PRGM STAT
    db '0147,', 0, 0, 'X', 0   ; 0 1 4 7 , SIN APPS XT?n undef
    db 0, 0, 0, 0, 0, 0        ; STO LN LOG x2 x-1 MATH
_rodata_sizeOfCharsLUT := $ - _rodata_characters

    ; uppercase letters
    db 10                      ; ENTER
    db 34, 'WRMH', 0, 0        ; + - × ÷ ^ undef
    db '?', 0, 'VQLG', 0, 0    ; (-) 3 6 9 ) TAN VARS undef
    db ':ZUPKFC', 0            ; . 2 5 8 ( COS PRGM STAT
    db ' YTOJEBX', 0           ; 0 1 4 7 , SIN APPS XT?n undef
    db 'XSNIDA'                ; STO LN LOG x2 x-1 MATH

    ; lowercase letters
    db 10                      ; ENTER
    db 34, 'wrmh', 0, 0        ; + - × ÷ ^ undef
    db '?', 0, 'vqlg', 0, 0    ; (-) 3 6 9 ) TAN VARS undef
    db ':zupkfc', 0            ; . 2 5 8 ( COS PRGM STAT
    db ' ytojebX', 0           ; 0 1 4 7 , SIN APPS XT?n undef
    db 'xsnida'   
