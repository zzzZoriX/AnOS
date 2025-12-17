[org 0x7c00]
[bits 16]

jmp run_in_16bit_mode


%include "disk_load.asm"
%include "gdt.asm"


run_in_16bit_mode:
; start initialization ;
cli
xor ax, ax
mov ds, ax
mov es, ax
mov ss, ax
mov sp, 0x7c00
mov [BOOT_DRIVE], dl

; load kernel from disk ;
mov bx, KERNEL_ADDRESS
mov dh, 0
mov dl, [BOOT_DRIVE]
mov al, 15
call disk_load

; switch to protected mode ;
cli
lgdt [gdt_descriptor]
mov eax, cr0
or eax, 1
mov cr0, eax

jmp CODE_SEG:pm_entry

[bits 32]
pm_entry:
mov ax, DATA_SEG
mov ds, ax
mov es, ax
mov ss, ax
mov fs, ax
mov gs, ax

mov esp, 0x90000

call KERNEL_ADDRESS

boot_halt:
hlt
jmp boot_halt


; data
BOOT_DRIVE: db 0
KERNEL_ADDRESS equ 0x1000

times 510 - ($ - $$) db 0
dw 0xaa55