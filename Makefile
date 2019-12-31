# Automatically generate lists of sources using wildcards .
C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h )

# Convert the *.c filenames to *.o to give a list of object files to build
OBJ = ${C_SOURCES:.c=.o}

# Defaul build target
all: kernel.elf

run: all
	qemu-system-x86_64 -kernel build\\kernel.elf

# Build the C code into binary
kernel.elf: boot/boot.o kernel/kernel.o ${OBJ}
	ld -T linker.ld -o build/kernel.bin $^
	objcopy -O elf32-i386 build/kernel.bin build/kernel.elf

# Generic rule for compiling C code to an object file
# For simplicity , we C files depend on all header files .
%.o : %.c ${HEADERS}
	gcc -ffreestanding -c $< -o $@

# Assemble the kernel_entry .
%.o : %.asm
	nasm $< -f elf32 -o $@

clean:
	del /s /q /f *.bin *.dis *.o *.tmp kernel.elf
	del /s /q /f kernel/*.o boot/*.bin drivers/*.o build/*