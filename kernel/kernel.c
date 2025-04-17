#include "utils.h"
#include "gdt.h"



void main(){
    const char* entry_message = "Welcome to LuxOS!";
    
    print_message(entry_message, video_memory, &index);
    init_gdt();
    print_message(entry_message, video_memory, &index);
    while(1);
}
