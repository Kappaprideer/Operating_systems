#ifndef LIBRARY_H
#define LIBRARY_H

typedef struct {
    char** array;
    int max_size;
    int size;
} chars_pointer;

chars_pointer* init(int size);
void count(chars_pointer* memory_blocks, char* filename);
char* show(chars_pointer* memory_blocks, int index);
void delete(chars_pointer* memory_blocks, int index);
void destroy(chars_pointer* memory_blocks);

#endif