#include "idt.h"
#include "../config.h"
#include "../memory/memory.h"
#include "../kernel.h"

struct idt_desc idt_descriptors[SANDERS_TOTAL_INTERRUPTS];
struct idtr_desc idtr_descriptor;

extern void idt_load(struct idtr_desc* ptr);

void idt_zero() {
    print("\nDivide by zero error!\n");
}

void idt_set(int interrupt_no, void* addr){
    struct idt_desc* desc = &idt_descriptors[interrupt_no];
    desc->offset_low = (uint32_t) addr & 0xffff;
    desc->selector = KERNEL_CODE_SELECTOR;
    desc->zero = 0x0;
    desc->type_attr = 0xee;
    desc->offset_high = (uint32_t)addr >> 16;
}

void idt_init() {
    memset(idt_descriptors, 0, sizeof(idt_descriptors));
    idtr_descriptor.limit = sizeof(idt_descriptors) -1;
    idtr_descriptor.base = (uint32_t)idt_descriptors;

    idt_set(0, idt_zero);

    idt_load(&idtr_descriptor);
}