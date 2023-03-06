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

void count_file(chars_pointer* memory_block, char* file_name){
    char buffer[200];
    sprintf(buffer, "wc %s > /tmp/wc_tmp_file.txt", file_name);
    system(buffer);
    system("stat /tmp/wc_tmp_file.txt -c \"%s\" > /tmp/wc_tmp_file_size.txt");

    FIle


    memory_block->array[memory_block->size]= (int*)malloc(sizeof(int));

    system("rm /tmp/wc_tmp_file.txt");
    system("rm /tmp/wc_tmp_file_size.txt");
}

// sprintf
void show_index(chars_pointer * memory ,int n) {
//    printf();
//    memory->array[n];
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