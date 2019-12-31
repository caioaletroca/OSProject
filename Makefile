# Automatically generate lists of sources using wildcards .
C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h )

# Convert the *.c filenames to *.o to give a list of object files to build
OBJ = ${C_SOURCES:.c=.o}

# Defaul build target
all: os-image.bin

run: all
	qemu-system-x86_64 build\\os-image.bin

# This is the actual disk image that the computer loads
# which is the combination of our compiled bootsector and kernel
os-image.bin: boot/boot.bin kernel/kernel.bin
	copy /b boot\\boot.bin + kernel\\kernel.bin build\\os-image.bin

# Build the C code into binary
kernel/kernel.bin: kernel/kernel_entry.o ${OBJ}
	ld -T NUL -o build/kernel.tmp -Ttext 0x1000 $^
	objcopy -O binary -j .text build/kernel.tmp kernel/kernel.bin

# Generic rule for compiling C code to an object file
# For simplicity , we C files depend on all header files .
%.o : %.c ${HEADERS}
	gcc -ffreestanding -c $< -o $@

# Assemble the kernel_entry .
%.o : %.asm
	nasm $< -f elf -o $@
%.bin : %.asm
	nasm $< -f bin -i boot -o $@

clean:
	del /s /q /f *.bin *.dis *.o *.tmp os-image.bin
	del /s /q /f kernel/*.o boot/*.bin drivers/*.o build/*