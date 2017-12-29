macro align value
{
  rb (value - 1) - ($ + value - 1) mod value
}

macro enum start, step, [items]
{
  common
    local count
    count = start
  forward
    items = count
    count = count + step
}

enum 0x0, 0x1, \
  ELFCLASSNONE,\
  ELFCLASS32,\
  ELFCLASS64

enum 0x0, 0x1, \
  ELFDATANONE,\
  ELFDATA2LSB,\
  ELFDATA2MSB

enum 0x0, 0x1,\
  EV_NONE,\
  EV_CURRENT

enum 0x0, 0x1,\
  ET_NONE,\
  ET_REL,\
  ET_EXEC,\
  ET_DYN,\
  ET_CORE
  ET_LOPROC = 0xFF00
  ET_HIPROC = 0xFFFF

enum 0x0, 0x1, \
  EM_NONE,\
  EM_M32,\
  EM_SPARC,\
  EM_386,\
  EM_68K,\
  EM_88K,\
  EM_RESERVED,\
  EM_860,\
  EM_MIPS

SHN_UNDEF         = 0x0
SHN_LORESERVE     = 0xFF00
SHN_LOPROC        = 0xFF00
SHN_HIPROC        = 0xFF1F
SHN_ABS           = 0xFFF1
SHN_COMMON        = 0xFFF2
SHN_HIRESERVE     = 0xFFFF

enum 0x0, 0x1, \
  PT_NULL,\
  PT_LOAD,\
  PT_DYNAMIC,\
  PT_INTERP,\
  PT_NOTE,\
  PT_SHLIB,\
  PT_PHDR
  PT_LOOS   = 0x60000000
  PT_HIOS   = 0x6FFFFFFF
  PT_LOPROC = 0x70000000
  PT_HIPROC = 0x7FFFFFFF

enum 0x0, 0x1, \
  PF_NONE,\
  PF_W,\
  PF_WX,\
  PF_R,\
  PF_RX,\
  PF_RW,\
  PF_RWX

struc e_ident elf_class, elf_data, elf_version {
e_ident_entry:
  .EI_MAG0     db 0x7F
  .EI_MAG3     db 'ELF'
  .EI_CLASS    db elf_class
  .EI_DATA     db elf_data
  .EI_VERSION  db elf_version
               rb e_ident_entry + 0x10 - $
}

struc elf_file_header entry, program_header, section_header, ph_entry_size, ph_entries_num, sh_entry_size, sh_entries_num {
local ..elf_file_header_entry
..elf_file_header_entry:
  .e_ident        e_ident ELFCLASS32, ELFDATA2LSB, EV_CURRENT
  .e_type         dw ET_EXEC
  .e_machine      dw EM_386
  .e_version      dd EV_NONE;EV_CURRENT
  .e_entry        dd entry
if program_header > 0x0
  .e_phoff        dd program_header - ..elf_file_header_entry
else
  .e_phoff        dd 0x0
end if
if section_header > 0x0
  .e_shoff        dd section_header - ..elf_file_header_entry
else
  .e_shoff        dd 0x0
end if
  .e_flags        dd 0x0
if program_header > 0x0
  .e_ehsize       dw program_header - ..elf_file_header_entry
else
  .e_ehsize        dw 0x0
end if
  .e_phentsize    dw ph_entry_size
  .e_phnum        dw ph_entries_num
  .e_shentsize    dw sh_entry_size
  .e_shnum        dw sh_entries_num
  .e_shstrndx     dw SHN_UNDEF
}

struc elf_program_header elf_base, elf_end, elf_bss, flags {
local ..elf_program_header_entry
..elf_program_header_entry:
  .p_type         dd PT_LOAD
  .p_offset       dd 0
  .p_vaddr        dd elf_base
  .p_paddr        dd 0
  .p_filesz       dd elf_bss - elf_base
  .p_memsz        dd elf_end - elf_base
  .p_flags        dd flags
  .p_align        dd 0x1000
elf_program_header_entry_size = $ - ..elf_program_header_entry
}
