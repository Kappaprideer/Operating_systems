#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct chars_pointer {
    int **array;
    int maxSize;
    int size;
} chars_pointer;

chars_pointer* init(int n){
    chars_pointer * memory_block = (chars_pointer*)malloc(sizeof(chars_pointer));
    memory_block->array = (int**)calloc(n,sizeof(int*));
    memory_block->maxSize =n;
    memory_block->size=0;
    return memory_block;
}

void count_file(chars_pointer* memoryBlocks, char* file_name){
    char buffer[200];
    sprintf(buffer, "wc %s > /tmp/test_file.txt", file_name);
    system(buffer);
    system("stat /tmp/test_file.txt -c \"%s\" > /tmp/gituwa.txt");
}

// sprintf
int* show_index(chars_pointer * memory ,int n) {
    return memory->array[n];
}


void destroy(chars_pointer * memory_block){
    free(memory_block->array);
}

int main() {

    chars_pointer* mem = init(20);
    count_file(mem, "/home/endrew/Github/Operating_systems/cw01/zad1/nowe.txt" );
    destroy(mem);


    return 0;
}