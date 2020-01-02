#include "../drivers/screen.h"
#include "utils.h"
#include "../cpu/idt.h"
#include "../cpu/isr.h"

void kmain() {
	clear_screen();

	isr_install();

    __asm__ __volatile__("int $1");
    //__asm__ __volatile__("int $3");
}