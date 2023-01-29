#include "idt.h"
#include "../config.h"
#include "../memory/memory.h"
#include "../kernel.h"
#include "../io/io.h"

struct idt_desc idt_descriptors[SANDERS_TOTAL_INTERRUPTS];
struct idtr_desc idtr_descriptor;

extern void idt_load(struct idtr_desc* ptr);
extern void int21h();
extern void no_interrupt();

void int21h_handler() {
    print("\nKeyPress!\n");
    outb(0x20, 0x20);
}

void no_interrupt_handler(){
    outb(0x20, 0x20);
}

void idt_set(int interrupt_no, void* addr){
    struct idt_desc* desc = &idt_descriptors[interrupt_no];
    desc->offset_low = (uint32_t)addr & 0xffff;
    desc->selector = KERNEL_CODE_SELECTOR;
    desc->zero = 0x0;
    desc->type_attr = 0xee;
    desc->offset_high = (uint32_t)addr >> 16;
}

void idt_init() {
    memset(idt_descriptors, 0, sizeof(idt_descriptors));
    idtr_descriptor.limit = sizeof(idt_descriptors) -1;
    idtr_descriptor.base = (uint32_t)idt_descriptors;

    for (int i = 0; i < SANDERS_TOTAL_INTERRUPTS; ++i) {
        idt_set(i, no_interrupt);
    }
    idt_set(0x21, int21h);

    idt_load(&idtr_descriptor);
}