#ifndef LIB_DYNAMICLIBRARY_H
#define LIB_DYNAMICLIBRARY_H

#include "library.h"
#include <dlfcn.h>

extern chars_pointer* (*_init_pointer) (int);
extern void (*_count) (chars_pointer* ,const char* );
extern char* (*_show) (chars_pointer *  ,int );
extern void (*_delete) (chars_pointer* , int );
extern void (*_destroy) (chars_pointer* );
extern int init_dynamic_handler(void);
extern void free_handler(void);

#endif