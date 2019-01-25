; std/functions.inc - standard functions
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

if ~ defined stdfunctions

define stdfunctions

write_string:
    mov bx, 9                       ; set page to zero and attribute to white
    mov ah, 0x0e                    ; BIOS subfunction: write character in tty
                                    ; mode
write_string_top:
    lodsb                           ; load byte at ds:si into al
    or al, al                       ; check if it's a null character
    jz write_string_done            ; exit on end of string
    int 0x10                        ; call BIOS interrupt 10h
    jmp write_string_top            ; print next character
write_string_done:
    ret
; writes a null-terminated string pointed at the ds:si

read_sector:
    pusha                           ; replace with correct segments
    mov si, 2                       ; set try counter to 2
read_sector_top:
    mov ah, 0x02                    ; BIOS subfunction read sectors
    int 0x13                        ; call BIOS interrupt 13h
    jnc read_sector_end             ; on no error exit function
    dec si                          ; decrement number of tries
    jc read_sector_end              ; exit if maximum tries
    xor ah, ah                      ; BIOS subfunction reset disk drives
    int 0x13                        ; call BIOS interrupt 13h
    jnc read_sector_top
read_sector_end:
    popa                            ; replace with correct segments
    ret
; reads sectors

end if
