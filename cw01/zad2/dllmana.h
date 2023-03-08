#ifndef _ONE_DYN_H
#define _ONE_DYN_H

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

static void* handle = NULL;

typedef struct chars_pointer {
    char** array;
    int max_size;
    int size;
} chars_pointer;

chars_pointer* (*_init)(int n);
void (*_count)(chars_pointer* memory_block, char* file_name);
char* (*_show)(chars_pointer * memory_blocks ,int n);
void (*_delete)(chars_pointer* memory_block, int index);
void (*_destroy)(chars_pointer * memory_blocks);

void init_dynamic_library()
{

    handle = dlopen("lib_one.so", RTLD_NOW);
    if (handle == NULL)
    {
        fprintf(stderr, "Error dynamic library open");
        return;
    }
    _init = dlsym(handle, "init");
    _count = dlsym(handle, "count");
    _show = dlsym(handle, "show");
    _delete = dlsym(handle, "delete");
    _destroy = dlsym(handle, "destroy");

    char *error;
    if ((error = dlerror()) != NULL)
    {
        fprintf(stderr, "%s\n", error);
        exit(1);
    }
}

chars_pointer* init(int n){
    return (*_init)(n);
}

void count(chars_pointer* memory_block, char* file_name){
    return (*_count)(memory_block, file_name);
}

char* show(chars_pointer * memory_blocks ,int n){
    return (*_show)(memory_blocks, n);
}

void delete(chars_pointer* memory_block, int index){
    return (*_delete)(memory_block, index);
}

void destroy(chars_pointer * memory_blocks){
    return (*_destroy)(memory_blocks);
}

#endif




