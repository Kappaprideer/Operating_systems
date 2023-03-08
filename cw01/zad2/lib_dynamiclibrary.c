#include <stdlib.h>
#include <stdio.h>
#include "lib_dynamiclibrary.h"

static void *handle = NULL;

chars_pointer* (*_init) (int);
void (*_count) (chars_pointer* ,const char* );
char* (*_show)(chars_pointer *  ,int );
void (*_delete)(chars_pointer* , int );
void (*_destroy)(chars_pointer * );



