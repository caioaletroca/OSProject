#ifndef __IDT_H__
#define __IDT_H__

// Constants
#define KERNEL_CS 0x08
#define IDT_ENTRIES 256

// Types
typedef struct {
    /**
     * The lower 16 bits of handler function address
     */
    short low_offset;

    /**
     * Kernel segment selector
     */
    short sel;

    /**
     * Unused data, always zero
     */
    char zero;

    /* 
     * First byte
     * Bit 7: "Interrupt is present"
     * Bits 6-5: Privilege level of caller (0=kernel..3=user)
     * Bit 4: Set to 0 for interrupt gates
     * Bits 3-0: bits 1110 = decimal 14 = "32 bit interrupt gate"
     */
    char flags; 

    /**
     * Higher 16 bits of handler function address
     */
    short high_offset;
} __attribute__((packed)) idt_gate_t;

/*
 * A pointer to the array of interrupt handlers.
 * Assembly instruction 'lidt' will read it
 */
typedef struct {
    short limit;
    int base;
} __attribute__((packed)) idt_register_t;

// Properties
idt_gate_t idt[IDT_ENTRIES];
idt_register_t idt_reg;

// Methods
void set_idt_gate(int n, int handler);
void set_idt();

#endif
