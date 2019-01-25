; std/macros.inc - standard macros
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

if ~ defined stdmacros

define stdmacros

macro puts str* {
    lea si, [str]                   ; loads message address into si
    call write_string               ; shows the message
}
; puts a string

macro reboot {
    db 0xea                         ; machine language to jump to ffff:0000
    dw 0x0000
    dw 0xffff
}
; reboots the machine

end if
