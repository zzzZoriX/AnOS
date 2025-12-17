gdt_start:
dq 0x0
dq 0x00cf9a000000ffff
dq 0x00cf92000000ffff
gdt_end:
gdt_descriptor:
dw gdt_end - gdt_start - 1
dd gdt_start

CODE_SEG equ 0x08
DATA_SEG equ 0x10