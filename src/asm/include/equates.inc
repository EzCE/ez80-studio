;--------------------------------------
;
; eZ80 Studio Source Code - equates.inc
; By RoccoLox Programs and TIny_Hacker
; Copyright 2022 - 2026
; License: GPL-3.0
;
;--------------------------------------

include 'ti84pceg.inc'

; Flags

sortFlag := ti.asm_Flag1
sortFirstItemFound := 0
sortFirstHidden := 1
sortSecondHidden := 2

; Editor

editBuffer := ti.vRam + ti.lcdWidth * ti.lcdHeight + 2

; Assembler

symbolTableStart := editBuffer + 65500 + 128

; SPI defines

spiValid := 8

; Lexer types
typeDefault := 3
typeLabel := 4
typeInstruction := 5
typeRegister := 6
typeCondition := 6
typeNumber := 7
typeParenthesis := 8
typeString := 9
typeComment := 10
typeModifier := 11

; use cursorImage RAM for these variables
;-----------------------------------------

EOF := ti.cursorImage

currentLineStart := EOF + 3
oldLineStart := currentLineStart + 3

; VAT / Filesystem

sortFirstItemFoundPtr := ti.mpLcdCrsrImage
sortEndOfPartPtr := ti.mpLcdCrsrImage + 3
sortVatEntrySize := ti.mpLcdCrsrImage + 6
sortVatEntryNewLoc := ti.mpLcdCrsrImage + 9
sortVatEntryTempEnd := ti.mpLcdCrsrImage + 12 + 15
