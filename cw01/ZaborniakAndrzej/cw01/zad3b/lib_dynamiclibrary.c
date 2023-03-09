#include <stdlib.h>
#include <stdio.h>
#include "lib_dynamiclibrary.h"

static void *handle = NULL;

chars_pointer *(*_init_pointer) (int);
void (*_count) (chars_pointer* ,const char* );
char* (*_show)(chars_pointer *  ,int );
void (*_delete)(chars_pointer* , int );
void (*_destroy)(chars_pointer* );

chars_pointer  *init_pointer(int size){
    return (*_init_pointer)(size);
}

void count(chars_pointer* memory_blocks, const char* filename){
    return (*_count)(memory_blocks, filename);
}

char* show(chars_pointer* memory_blocks, int index){
    return (*_show)(memory_blocks, index);
}

void delete(chars_pointer* memory_blocks, int index){
    return (*_delete)(memory_blocks, index);
}

void destroy(chars_pointer* memory_blocks){
    return (*_destroy)(memory_blocks);
}

int init_dynamic_handler(void){
    handle = dlopen("./lib_one.so", RTLD_LAZY);
    *((void **) &(_init_pointer)) = dlsym(handle, "init_pointer");
    *((void **) &(_count)) = dlsym(handle, "count");
    *((void **) &(_show)) = dlsym(handle, "show");
    *((void **) &(_delete)) = dlsym(handle, "delete");
    *((void **) &(_destroy)) = dlsym(handle, "destroy");

    return 0;
}


void free_handler(void){
    dlclose(handle);
}