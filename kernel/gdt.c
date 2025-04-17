#include "gdt.h"
#include "utils.h"

void set_gdt_entry(int num, uint16_t base_low, uint8_t base_middle, uint8_t base_high, uint16_t limit_low, uint8_t access, uint8_t granularity){

}

void init_gdt(){
    const char* init_message = "Initializing GDT table...";
    print_message(init_message, video_memory, &index);
}