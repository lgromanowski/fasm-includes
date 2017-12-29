; fasm example.asm
; chmod +x example.bin

include 'includes/elf_x86.inc'
include 'includes/syscall.inc'
include 'includes/unistd.inc'

empty_section_header = 0x0    ; Offset to section header

program_base = 0x700000
org     program_base
use32

file_header:
  elf      elf_file_header  entry_point,\
                            program_header,\
                            empty_section_header,\
                            elf_program_header_entry_size,\
                            program_header_size / elf_program_header_entry_size,\
                            0, 0
program_header:
  ph       elf_program_header program_base, program_end, bss, PF_RWX
program_header_size = $ - program_header

entry_point:
    mov     ecx, msg
    mov     edx, msg_size
    mov     eax, sys_write
    mov     ebx, STDOUT
    int     0x80

    mov     eax, sys_exit
    xor     ebx, ebx
    int     0x80

msg db 'Hello world!', 0x0A
msg_size = $ - msg

bss:
program_end:
