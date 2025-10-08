#include "./utils/utils.h"
#include "./gdt/gdt.h"
#include "./idt/idt.h"

uint8_t kernel_stack[4096];

void main(){
    uint32_t stack_top = (uint32_t)(kernel_stack + 4096);
    asm volatile("movl %0, %%esp" :: "r"(stack_top));

    print_message("Welcome to LuxOS\n", video_memory, &index);
    init_gdt();
    idt_setup();
    asm volatile("int $128");

    while(1);
}
