#include "isr.h"
#include "idt.h"
#include "../drivers/screen.h"
#include "../kernel/utils.h"

/**
 * Constants
 */
char *exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

/**
 * Creates the ISR system
 */
void isr_install() {
    set_idt_gate(0, (int)isr0);
    set_idt_gate(1, (int)isr1);
    set_idt_gate(2, (int)isr2);
    set_idt_gate(3, (int)isr3);
    set_idt_gate(4, (int)isr4);
    set_idt_gate(5, (int)isr5);
    set_idt_gate(6, (int)isr6);
    set_idt_gate(7, (int)isr7);
    set_idt_gate(8, (int)isr8);
    set_idt_gate(9, (int)isr9);
    set_idt_gate(10, (int)isr10);
    set_idt_gate(11, (int)isr11);
    set_idt_gate(12, (int)isr12);
    set_idt_gate(13, (int)isr13);
    set_idt_gate(14, (int)isr14);
    set_idt_gate(15, (int)isr15);
    set_idt_gate(16, (int)isr16);
    set_idt_gate(17, (int)isr17);
    set_idt_gate(18, (int)isr18);
    set_idt_gate(19, (int)isr19);
    set_idt_gate(20, (int)isr20);
    set_idt_gate(21, (int)isr21);
    set_idt_gate(22, (int)isr22);
    set_idt_gate(23, (int)isr23);
    set_idt_gate(24, (int)isr24);
    set_idt_gate(25, (int)isr25);
    set_idt_gate(26, (int)isr26);
    set_idt_gate(27, (int)isr27);
    set_idt_gate(28, (int)isr28);
    set_idt_gate(29, (int)isr29);
    set_idt_gate(30, (int)isr30);
    set_idt_gate(31, (int)isr31);

    set_idt(); // Load with ASM
}

void isr_handler(registers_t r) {
    print("Received Interrupt: ");
    print("\n");
    print(exception_messages[r.int_no]);
    print("\n");
}
