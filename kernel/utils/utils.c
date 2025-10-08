#include "utils.h"

char* video_memory = (char*) VIDEO_ADDR;
int index = 0;


void print_message(const char *message, char *video_memory, int *index_ptr){
    for(int i = 0; message[i] != '\0'; i++){
        if(message[i] == '\n'){   // trata nova linha
            *index_ptr = ((*index_ptr) / SCREEN_WIDTH + 1) * SCREEN_WIDTH;
            continue;
        }
        video_memory[(*index_ptr)*2] = message[i];
        video_memory[(*index_ptr)*2 + 1] = 0x07; // cor padrão
        (*index_ptr)++;
        if(*index_ptr >= SCREEN_WIDTH * SCREEN_HEIGHT){  // simples scroll
            *index_ptr = 0;
        }
    }
}

