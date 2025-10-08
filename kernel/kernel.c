#include "utils.h"
#include "gdt.h"



void main(){
    print_message("Welcome to LuxOS\n", video_memory, &index);
    init_gdt();
    while(1);
}
