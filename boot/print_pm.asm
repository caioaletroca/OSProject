; Print Method in Protected Mode

[bits 32]

VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

print_pm:
	pusha
	mov edx, VIDEO_MEMORY

print_pm_start:
	mov al, [ebx]				; The address of the char
	mov ah, WHITE_ON_BLACK 		; Sets the color

	cmp al, 0					; Check if is a end of string
	je print_pm_done

	mov [edx], ax				; Stores data in video memory
	add ebx, 1					; Next char
	add edx, 2					; Next video memory position

	jmp print_pm_start

print_pm_done:
	popa
	ret