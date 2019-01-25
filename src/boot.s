; boot.s - main loader
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

format elf64
use16
section '.text'
org 0x0600

include 'std/macros.inc'
include 'mbr/macros.inc'

main:
    init                            ; initialise segments
    jmp 0:start                     ; jump to the start of the program

no_active:
    puts noactivemsg                ; shows no active message
    jmp short error                 ; go to error

no_data:
    puts nodatamsg                  ; shows no data message
    jmp short error                 ; go to error

bad_read:
    puts badreadmsg                 ; shows bad read message
    jmp short error                 ; go to error

no_bootable:
    puts nobootablemsg              ; shows no bootable message

error:
    puts rebootmsg                  ; shows reboot message
    xor ax, ax                      ; BIOS subfunction read character
    int 0x16                        ; call BIOS interrupt 16h
    reboot                          ; reboot the machine

start:
    mov [drive], dl                 ; store drive number
    seek_active pt1                 ; search for the active partition
    jc no_active                    ; jump to error on no active
    mov [offset], bx                ; store found partition offset

    xor ecx, ecx                    ; clear ecx
    mov ah, 0x08                    ; BIOS subfunction: get drive parameters
    int 0x13                        ; call BIOS interrupt 13h
    jc no_data                      ; exit on error
    xor ch, ch                      ; clear high cylinder
    and cl, 0x3f                    ; obtain number of sectors per track
    xor ebx, ebx                    ; clear ebx
    add dh, 1                       ; obtain the number of heads
    mov bl, dh

    mov ax, [offset]                ; point to the active partition
    mov eax, [eax + 0x08]           ; set eax to the LBA value
    xor edx, edx                    ; clear edx
    div ecx                         ; divide (eax:edx/ecx) to (eax, edx)
                                    ; quotient eax: LBA / sectors per track
                                    ; remainder edx: LBA mod sectors per track
    inc dx                          ; add one to remainder to obtain sector
    mov cl, dl                      ; set cl to the sector number
    xor edx, edx                    ; clear edx
    div ebx                         ; divide (eax:edx/ebx) to (eax, edx)
                                    ; quotient eax:
                                    ; (LBA / sectors per track) / heads
                                    ; remainder edx:
                                    ; (LBA / sectors per track) mod heads
    xchg dl, dh                     ; set dh to the head number
    mov ch, al                      ; set ch to the low cylinder number
    shr ax, 2                       ; shift to obtain highest bits
    and al, 0xc0                    ; only the two highest bits
    or cl, al                       ; set highest bits of cl to the cylinder
    mov dl, [drive]                 ; set dl to the drive number
    mov bx, 0x7c00                  ; set bx to the memory destination
    mov ax, 0x0201                  ; BIOS subfunction: read sectors into memory
                                    ; set al to read one sector
    call read_sector                ; call function to read sectors
    jc bad_read                     ; go to error on no read

    cmp word[0x7dfe], 0xaa55        ; check boot signature
    jne no_bootable                 ; jump to error on no bootable
    mov si, word[offset]            ; set si to the partition offset
    mov dl, byte[drive]             ; set dl to the drive
    jmp 0x7c00                      ; jump to vbr

include 'std/functions.inc'

noactivemsg db "no active partition", 13, 10, 0
nodatamsg db "no data from disk", 13, 10, 0
badreadmsg db "error reading from disk", 13, 10, 0
nobootablemsg db "no bootable partition", 13, 10, 0
rebootmsg db "press any key to reboot...", 0

drive db 0
offset dw 0

times 436-($-$$) db 0x90

uid: times 10 db 0

include 'mbr/partitions.inc'

bootmagic:
    db 0x55
    db 0xaa
