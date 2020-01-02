#include "idt.h"
#include "../kernel/utils.h"

/**
 * Sets a specific entry on the IDT
 * @param n       [description]
 * @param handler [description]
 */
void set_idt_gate(int n, int handler) {
    idt[n].low_offset = (short)((handler) & 0xFFFF);
    idt[n].sel = KERNEL_CS;
    idt[n].zero = 0;
    idt[n].flags = 0x8E; 
    idt[n].high_offset = (short)(((handler) >> 16) & 0xFFFF);
}

/**
 * Sets the IDT register size
 */
void set_idt() {
    idt_reg.base = (int) &idt;
    idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;
    
    __asm__ __volatile__(
    	"lidtl (%0)" : : "r" (&idt_reg)
	);
}
