nasm -f elf32 boot/boot.asm -o boot/boot.o
gcc -m32 -c kernel/kernel.c -o kernel/kernel.o -ffreestanding -nostdlib -nostdinc
ld -T linker.ld -o kernel.bin boot/boot.o drivers/screen.o drivers/ports.o kernel/kernel.o -build-id=none
objcopy -O elf32-i386 kernel.bin kernel.elf