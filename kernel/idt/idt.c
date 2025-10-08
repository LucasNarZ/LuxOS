#include "idt.h"
#include "../utils/utils.h"

struct idt_entry idt[256];
struct idt_ptr idtp;

extern void idt_load();

void* isr_table[32] = {
    isr0, isr1, isr2, isr3, isr4, isr5, isr6, isr7,
    isr8, isr9, isr10, isr11, isr12, isr13, isr14, isr15,
    isr16, isr17, isr18, isr19, isr20, isr21, isr22, isr23,
    isr24, isr25, isr26, isr27, isr28, isr29, isr30, isr31
};

void* irq_table[16] = {
    irq0, irq1, irq2, irq3, irq4, irq5, irq6, irq7,
    irq8, irq9, irq10, irq11, irq12, irq13, irq14, irq15
};

static inline void outb(uint16_t port, uint8_t val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

void idt_set_entry(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[num].base_low = base & 0xFFFF;
    idt[num].base_high = (base >> 16) & 0xFFFF;
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

void pic_remap(){
    outb(0x20, 0x11);
    outb(0xA0, 0x11);

    outb(0x21, 0x20);
    outb(0xA1, 0x28);

    outb(0x21, 0x04);
    outb(0xA1, 0x02);

    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    
    outb(0x21, 0x00);
    outb(0xA1, 0x00);
}

void setup_idt_entries(void) {
    // Exceptions (CPU ISRs 0–31)
    for (int i = 0; i < 32; i++) {
        idt_set_entry(i, (uint32_t)isr_table[i], 0x08, 0x8E);
    }

    // IRQs (hardware, 32–47)
    for (int i = 0; i < 16; i++) {
        idt_set_entry(32 + i, (uint32_t)irq_table[i], 0x08, 0x8E);
    }

    // Syscalls (software interrupts)
    idt_set_entry(128, (uint32_t)isr128, 0x08, 0x8E);
    idt_set_entry(177, (uint32_t)isr177, 0x08, 0x8E);
}



void idt_setup() {
    print_message("Initializing IDT...\n", video_memory, &index);
    idtp.limit = (sizeof(struct idt_entry) * 256) - 1;
    idtp.base = (uint32_t)&idt;

    pic_remap();   

    setup_idt_entries(); 

    print_message("IDT Initialized sucessefuly\n", video_memory, &index);
}




const char* exception_messages[] = 
{
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
    "Double fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment not present",
    "Stack fault",
    "General protection fault",
    "Page fault",
    "Unknown Interrupt",
    "Coprocessor Fault",
    "Alignment Fault",
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

void isr_handler(struct interrupt_registers* regs)
{
    if (regs->int_no < 32)
    {
        print_message(exception_messages[regs->int_no], video_memory, &index);

        for (;;);
    }
}
