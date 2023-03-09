#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

//typedef struct chars_pointer {
//    char** array;
//    int max_size;
//    int size;
//} chars_pointer;

chars_pointer* init_pointer(int n){
    chars_pointer* memory_block = (chars_pointer*) malloc(sizeof(chars_pointer));
    memory_block->array = (char **) calloc(n, sizeof(char *));
    memory_block->max_size =n;
    memory_block->size=0;
    return memory_block;
}

// usuwanie EXITA !!!!!
void check_if_file_exist(FILE* f){
    if(f == NULL){
        fprintf(stderr, "File not found! \n");
        exit(1);
    }
}

int get_file_size(char* file_name){
    int size;
    FILE *file;
    file = fopen(file_name, "rb");
    check_if_file_exist(file);
    fseek(file, 0, SEEK_END);
    size = (int) ftell(file);
    fclose(file);
    return size;
}

void count(chars_pointer* memory_block,const char* file_name){
    if(memory_block == NULL){
        fprintf(stderr, "You have to initalize structure first!\n");
    }
    else if(memory_block->size >= memory_block->max_size)
        fprintf(stderr, "You can not count another file, array is full! \n");
    else {
        int empty_cell_index=0;
        while(empty_cell_index < memory_block->max_size && memory_block->array[empty_cell_index] != NULL){
            empty_cell_index++;
        }

        char* buffer = (char*) calloc(sizeof(char),strlen(file_name)+26);
        sprintf(buffer, "wc %s > /tmp/wc_tmp_file.txt", file_name);
        system(buffer);
        free(buffer);

        int file_size = get_file_size("/tmp/wc_tmp_file.txt");
        memory_block->array[empty_cell_index] = (char*) malloc(sizeof(char) * file_size);

        FILE *wc_file = fopen("/tmp/wc_tmp_file.txt", "r");
        check_if_file_exist(wc_file);

        fgets(memory_block->array[empty_cell_index], file_size, wc_file);
        fclose(wc_file);

//        system("rm /tmp/wc_tmp_file.txt");

        memory_block->size++;
    }
}


char* show(chars_pointer * memory_blocks ,int n) {
    if(memory_blocks == NULL){
        fprintf(stderr, "Structure is not initalized!\n");
        return "";
    }
    else if (n >= memory_blocks->max_size || memory_blocks->array[n] == 0) {
        fprintf(stderr, "Wrong index! \n");
        return "";
    }
    else {
        return memory_blocks->array[n];
    }
}

void delete(chars_pointer* memory_block, int index){
    if(memory_block == NULL){
        fprintf(stderr, "Structure is not initialized! \n");
    }
    else if(index > memory_block->size)
        fprintf(stderr, "Index is bigger than array size! \n");
    else if(memory_block->array[index] == 0){
        fprintf(stderr, "Array is already empty at index: %d \n", index);
    }
    else{
    memory_block->size--;
    free(memory_block->array[index]);
    memory_block->array[index]=0;
    }
}

void destroy(chars_pointer * memory_blocks){
    if(memory_blocks == NULL){
        fprintf(stderr, "Structure is not initialized! \n");
    }
    else{
        for(int i=0; i<memory_blocks->size; i++){
            free(memory_blocks->array[i]);
            memory_blocks->array[i]=0;
        }
        memory_blocks->size=0;
    }
}