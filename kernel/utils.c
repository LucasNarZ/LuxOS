#include "utils.h"

char* video_memory = (char*) VIDEO_ADDR;
int index = 0;

void print_message(const char *message, char *video_memory, int *index_ptr){
    for(int i = 0; message[i] != '\0';i++){
        video_memory[(*index_ptr)*2] = message[i];
        video_memory[(*index_ptr)*2+1] = 0x07;
        (*index_ptr)++;
    }
    *index_ptr += (SCREEN_WIDTH - sizeof(*message)*2);
}
