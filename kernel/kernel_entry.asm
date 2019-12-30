[bits 32]
[extern _kmain]

call _kmain				; Invoke kmain() in the C kernel
jmp $