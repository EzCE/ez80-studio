; Copyright 2015-2021 Matt "MateoConLechuga" Waltz
;
; Redistribution and use in source and binary forms, with or without
; modification, are permitted provided that the following conditions are met:
;
; 1. Redistributions of source code must retain the above copyright notice,
;    this list of conditions and the following disclaimer.
;
; 2. Redistributions in binary form must reproduce the above copyright notice,
;    this list of conditions and the following disclaimer in the documentation
;    and/or other materials provided with the distribution.
;
; 3. Neither the name of the copyright holder nor the names of its contributors
;    may be used to endorse or promote products derived from this software
;    without specific prior written permission.
;
; THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
; IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
; ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
; LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
; CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
; SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
; INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
; CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
; ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
; POSSIBILITY OF SUCH DAMAGE.

; made by martin warmer, mmartin@xs4all.nl
; modified for eZ80 architecture and hidden programs by matt waltz
;
; uses insertion sort to sort the vat alphabetically

	assume adl=1

	section .text

include 'include/equates.inc'

	public _asm_misc_SortVAT

_asm_misc_SortVAT:
    ld iy, ti.flags
    ld a, (iy + sortFlag)
    push af
    call misc_SortVatInternal
    pop af
    ld (iy + sortFlag), a
    ret

misc_SortVatInternal:
    res sortFirstItemFound, (iy + sortFlag)
    ld hl, (ti.progPtr)

.sortNext:
    call .findNextItem
    ret nc

.foundItem:
    bit sortFirstItemFound, (iy + sortFlag)
    jp z, .firstFound
    push hl
    call .skipName
    pop de
    push hl ; to continue from later on
    ld hl, (sortFirstItemFoundPtr)
    jr .searchNextStart ; could speed up sorted list by first checking if it's the last item (not neccessary)

.searchNext:
    call .skipName
    ld bc, (sortEndOfPartPtr)
    or a, a ; reset carry flag
    push hl
    sbc hl, bc
    pop hl
    jr z, .locationFound
    ld bc, -6
    add hl, bc

.searchNextStart:
    push hl
    push de
    call .compareNames
    pop de
    pop hl
    jr nc, .searchNext

.searchNextEnd:
    ld bc, 6
    add hl, bc ; goto start of entry

.locationFound:
    ex de, hl
    ld a, (hl)
    add a, 7
    ld bc, 6 ; rewind six bytes
    add hl, bc ; a = number of bytes to move
    ld c, a ; hl -> bytes to move
    ld (sortVatEntrySize), bc ; de -> move to location
    ld (sortVatEntryNewLoc), de
    push de
    push hl
    or a, a
    sbc hl, de
    pop hl
    pop de
    jr z, .noMoveNeeded
    push hl
    ld de, sortVatEntryTempEnd
    lddr ; copy entry to move to sortVatEntryTempEnd
    ld hl, (sortVatEntryNewLoc)
    pop bc
    push bc
    or a, a
    sbc hl, bc
    push hl
    pop bc
    pop hl
    inc hl
    push hl
    ld de, (sortVatEntrySize)
    or a, a
    sbc hl, de
    ex de, hl
    pop hl
    ldir
    ld hl, sortVatEntryTempEnd
    ld bc, (sortVatEntrySize)
    ld de, (sortVatEntryNewLoc)
    lddr
    ld hl, (sortEndOfPartPtr)
    ld bc, (sortVatEntrySize)
    or a, a
    sbc hl, bc
    ld (sortEndOfPartPtr), hl
    pop hl ; pointer to continue from
    jp .sortNext ; to skip name and rest of entry

.noMoveNeeded:
    pop hl
    ld (sortEndOfPartPtr), hl
    jp .sortNext

.firstFound:
    set sortFirstItemFound, (iy + sortFlag)
    ld (sortFirstItemFoundPtr), hl ; to make it only execute once
    call .skipName
    ld (sortEndOfPartPtr), hl
    jp .sortNext

.skipToNext:
    ld bc, -6
    add hl, bc
    call .skipName
    jp .findNextItem ; look for next item

.skipName:
    ld bc, 0
    ld c, (hl) ; number of bytes in name
    inc c ; to get pointer to data type byte of next entry
    or a, a ; reset carry flag
    sbc hl, bc
    ret

.compareNames: ; hl and de pointers to strings output=carry if de is first
    res sortFirstHidden, (iy + sortFlag)
    res sortSecondHidden, (iy + sortFlag)
    dec hl
    dec de
    ld b, 64
    ld a, (hl)
    cp a, b
    jr nc, .firstNotHidden ; check if files are hidden
    add a, b
    ld (hl), a
    set sortFirstHidden, (iy + sortFlag)

.firstNotHidden:
    ld a, (de)
    cp a, b
    jr nc, .secondNotHidden
    add a, b
    ld (de), a
    set sortSecondHidden, (iy + sortFlag)

.secondNotHidden:
    push hl
    push de
    inc hl
    inc de
    ld b, (hl)
    ld a, (de)
    ld c, 0
    cp a, b ; check if same length
    jr z, .compareNameContinue
    jr nc, .compareNameContinue ; b = smaller than a
    inc c ; to remember that b was larger
    ld b, a ; b was larger than a

.compareNameContinue:
    dec hl
    dec de
    ld a, (de)
    cp a, (hl)
    jr nz, .match
    djnz .compareNameContinue
    pop de
    pop hl
    call .resetHiddenFlags
    dec c
    ret nz
    ccf
    ret

.match:
    pop de
    pop hl

.resetHiddenFlags:
    push af
    bit sortFirstHidden, (iy + sortFlag)
    jr z, .firstNotHiddenCheck
    ld a, (hl)
    sub a, 64
    ld (hl), a

.firstNotHiddenCheck:
    bit sortSecondHidden, (iy + sortFlag)
    jr z, .secondNotHiddenCheck
    ld a, (de)
    sub a, 64
    ld (de), a

.secondNotHiddenCheck:
    pop af
    ret

.findNextItem: ; carry = found, nc = notfound
    ex de, hl
    ld hl, (ti.pTemp)
    or a, a ; reset carry flag
    sbc hl, de
    ret z
    ex de, hl ; load progptr into hl
    ld a, (hl)
    and a, $1F ; mask out state bytes
    push hl
    ld hl, misc_SortTypes
    ld bc, misc_SortTypes.length
    cpir
    pop hl
    jp nz, .skipToNext ; skip to next entry
    dec hl ; add check for folders here if needed
    dec hl
    dec hl ; to pointer
    ld e, (hl)
    dec hl
    ld d, (hl) ; pointer now in de
    dec hl
    ld a, (hl) ; high byte now in a
    dec hl ; add check: do I need to sort this program (not necessary)
    scf
    ret

misc_SortTypes:
    db ti.ProgObj, ti.ProtProgObj, ti.AppVarObj
.length := $-.
