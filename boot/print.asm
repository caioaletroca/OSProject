; Prints a String
print:
	pusha

; Prints a string in memory using the BIOS functions
print_start:
	mov al, [bx]
	cmp al, 0
	je print_done

	mov ah, 0x0e
	int 0x10

	add bx, 1
	jmp print_start

print_done:
	popa
	ret

; Prints the end of line chars
print_ln:
	pusha

	mov ah, 0x0e
	mov al, 0x0a			; New line char
	int 0x10
	mov al, 0x0d			; Carriage return
	int 0x10

	popa
	ret