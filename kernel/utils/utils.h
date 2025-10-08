#ifndef UTILS_H
#define UTILS_H

#define VIDEO_ADDR 0xB8000
#define SCREEN_WIDTH 80 
#define SCREEN_HEIGHT 40

extern char* video_memory;
extern int index;

void print_message(const char *message, char *video_memory, int *index_ptr);

#endif
