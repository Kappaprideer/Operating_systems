#ifndef ZAD1_LIBRARY_H
#define ZAD1_LIBRARY_H

typedef struct chars_pointer{} chars_pointer;
chars_pointer* init(int n);
void count(chars_pointer*, char*);
char* show(chars_pointer*, int);
void delete(chars_pointer*, int);
void destroy(chars_pointer*);


#endif