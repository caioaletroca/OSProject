; Defined in isr.c
[extern _isr_handler]

; Common ISR code
isr_common_stub:
    ; Save CPU state
	pusha                      ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax
	mov ax, ds                 ; Lower 16-bits of eax = ds.
	push eax                   ; save the data segment descriptor
	mov ax, 0x10               ; kernel data segment descriptor
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	
    ; Call C handler
	call _isr_handler
	
    ; Restore state
	pop eax 
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	popa
	add esp, 8                 ; Cleans up the pushed error code and pushed ISR number
	sti
	iret                       ; Pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP
	
; Error routines
%macro ISR_NO_ERROR_CODE 1
[global _isr%1]
_isr%1:
    cli
    push byte 0
    push byte %1
    jmp isr_common_stub
%endmacro

%macro ISR_ERROR_CODE 1
[global _isr%1]
_isr%1:
    cli
    push byte %1
    jmp isr_common_stub
%endmacro

ISR_NO_ERROR_CODE 0
ISR_NO_ERROR_CODE 1
ISR_NO_ERROR_CODE 2
ISR_NO_ERROR_CODE 3
ISR_NO_ERROR_CODE 4
ISR_NO_ERROR_CODE 5
ISR_NO_ERROR_CODE 6
ISR_NO_ERROR_CODE 7
ISR_ERROR_CODE 8
ISR_NO_ERROR_CODE 9
ISR_ERROR_CODE 10
ISR_ERROR_CODE 11
ISR_ERROR_CODE 12
ISR_ERROR_CODE 13
ISR_ERROR_CODE 14
ISR_NO_ERROR_CODE 15
ISR_NO_ERROR_CODE 16
ISR_NO_ERROR_CODE 17
ISR_NO_ERROR_CODE 18
ISR_NO_ERROR_CODE 19
ISR_NO_ERROR_CODE 20
ISR_NO_ERROR_CODE 21
ISR_NO_ERROR_CODE 22
ISR_NO_ERROR_CODE 23
ISR_NO_ERROR_CODE 24
ISR_NO_ERROR_CODE 25
ISR_NO_ERROR_CODE 26
ISR_NO_ERROR_CODE 27
ISR_NO_ERROR_CODE 28
ISR_NO_ERROR_CODE 29
ISR_NO_ERROR_CODE 30
ISR_NO_ERROR_CODE 31
