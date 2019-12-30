@echo off

:: Compiles the Boot and Kernel Assembly
nasm -f bin boot/boot.asm -i boot -o boot/boot.bin
nasm kernel/kernel_entry.asm -f elf -o kernel/kernel_entry.o

:: Compile the C kernel
gcc -ffreestanding -c kernel/kernel.c -o kernel/kernel.o

:: Link Assembly Kernel with C version
ld -T NUL -o kernel/kernel.tmp -Ttext 0x1000 kernel/kernel_entry.o kernel/kernel.o

:: Join in a binary file
objcopy -O binary -j .text kernel/kernel.tmp kernel/kernel.bin 

:: Merge the boot and the kernel
copy /b boot\\boot.bin + kernel\\kernel.bin os-image

:: Delete intermediate and temporary files
echo Deleting compilation files
del /s /q /f *.bin *.o *.tmp