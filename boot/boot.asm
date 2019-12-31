
; BOOT LOADER
[org 0x7c00]
KERNEL_OFFSET equ 0x1000				; Memory offset of the kernel

	mov [BOOT_DRIVE], dl

	mov bp, 0x9000						; Set the stack pointer
	mov sp, bp

	mov bx, MSG_REAL_MODE
	call print
	call print_ln

	call load_kernel 					; Loads kernel from disk

	call switch_to_pm					; Note that we never returns

	jmp $

; Add the extra files
%include "print.asm"
%include "print_hex.asm"
%include "disk_load.asm"
%include "gdt.asm"
%include "print_pm.asm"
%include "switch.asm"

[bits 16]

load_kernel:
	mov bx, MSG_LOAD_KERNEL
	call print
	call print_ln

	mov bx, KERNEL_OFFSET 				; Set -up parameters for our disk_load routine , so
	mov dh, 2 							; that we load the first 15 sectors ( excluding
	mov dl, [BOOT_DRIVE]				; the boot sector ) from the boot disk ( i.e. our
	call disk_load 						; kernel code ) to address KERNEL_OFFSET

	ret

[bits 32]

; Start of Protected Mode
BEGIN_PM:

	mov ebx, MSG_PROT_MODE
	call print_pm

	call KERNEL_OFFSET 					; Call the C Kernel
	
	jmp $								; Hang

; Global Variables
BOOT_DRIVE		db 0
MSG_REAL_MODE	db "Started the 16-bit Real Mode", 0
MSG_PROT_MODE	db "Successfully enabled the 32-bit Protected Mode", 0
MSG_LOAD_KERNEL db "Loading kernel into memory", 0

; Bootsector padding Magic Number
times 510-($-$$) db 0
dw 0xaa55