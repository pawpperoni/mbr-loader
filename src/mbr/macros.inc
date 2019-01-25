; mbr/macros.inc - MBR macros
; Copyright (C) 2019  Bruno Mondelo

; This program is free software: you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation, either version 3 of the License, or
; (at your option) any later version.

; This program is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.

; You should have received a copy of the GNU General Public License
; along with this program.  If not, see <https://www.gnu.org/licenses/>.

if ~ defined mbrmacros

define mbrmacros

macro init {
    cli                             ; disable interrupts
    xor cx, cx                      ; clear cx
    mov ax, cx                      ; clear ax
    mov ds, ax                      ; clear ds
    mov es, ax                      ; clear es
    mov ss, ax                      ; clear ss
    mov sp, ax                      ; clear sp
    cld                             ; clear direction flag
copy_lower:
    mov cx, 0x0100                  ;
    mov si, 0x7c00                  ;
    mov di, 0x0600                  ;
    rep movsw                       ;
    sti                             ; enable interrupts
}
; initialises the segments

macro seek_active pt* {
    clc                             ; clear the carry flag
    mov bx, pt                      ; set bx to first partition
    mov cx, 4                       ; set cx to counter
seek_active_top:
    mov al, byte [bx]               ; set al to the active flag
    test al, 0x80                   ; compare to the active flag
    jne seek_active_end             ; jump to end if found
    add bx, 0x10                    ; point to next partition
    dec cx                          ; decrement counter
    cmp cx, 0                       ; compare to last iteration
    jnz seek_active_top             ; check next entry
    stc                             ; set the carry flag on error
seek_active_end:
}
; seeks the active partition

end if
