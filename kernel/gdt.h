#include <stdint.h>
#ifndef GDT_H
#define GDT_H


struct gdt_entry{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t base_high;
    uint8_t access;
    uint8_t granularity;
}__attribute__((packed));


struct gdt_entry_prt {
    uint16_t limit;
    uint32_t base;
}__attribute__((packed));

void set_gdt_entry(int num, uint16_t base_low, uint8_t base_middle, uint8_t base_high, uint16_t limit_low, uint8_t access, uint8_t granularity);
void init_gdt();

#endif