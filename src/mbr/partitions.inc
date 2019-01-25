; mbr/partitions.inc - MBR partition table
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

pt1:
pt1_attributes: db 0
pt1_start: times 3 db 0
pt1_type: db 0
pt1_end: times 3 db 0
pt1_lba: times 4 db 0
pt1_size: times 4 db 0

pt2:
pt2_attributes: db 0
pt2_start: times 3 db 0
pt2_type: db 0
pt2_end: times 3 db 0
pt2_lba: times 4 db 0
pt2_size: times 4 db 0

pt3:
pt3_attributes: db 0
pt3_start: times 3 db 0
pt3_type: db 0
pt3_end: times 3 db 0
pt3_lba: times 4 db 0
pt3_size: times 4 db 0

pt4:
pt4_attributes: db 0
pt4_start: times 3 db 0
pt4_type: db 0
pt4_end: times 3 db 0
pt4_lba: times 4 db 0
pt4_size: times 4 db 0
