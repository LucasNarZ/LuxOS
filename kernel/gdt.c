#include "gdt.h"
#include "utils.h"

void set_gdt_entry(int num, uint16_t base_low, uint8_t base_middle, uint8_t base_high, uint16_t limit_low, uint8_t access, uint8_t granularity){

}

void init_gdt(){
    print_message("Initializing GDT table...\n", video_memory, &index);

}
