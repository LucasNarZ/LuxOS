#include <stdint.h>
#ifndef GDT_H
#define GDT_H

#define GDT_ENTRIES 3  // NULL, Code, Data

struct gdt_entry {
    uint16_t limit_low;      // bits 0-15 do tamanho reservado
    uint16_t base_low;       // bits 0-15 do endereço
    uint8_t  base_middle;    // bits 16-23 do endereço
    uint8_t  access;         // flags de acesso
    uint8_t  granularity;    // tamanho reservado (bits 16-19) + flags
    uint8_t  base_high;      // bits 24-31 do endereço
} __attribute__((packed));

struct gdt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

extern struct gdt_entry gdt[GDT_ENTRIES];
extern struct gdt_ptr gdtp;


void gdt_set_entry(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran); 
void init_gdt();

#endif
