#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct memoryBlocks {
    int *array;
    int maxSize;
    int size;
} memoryBlocks;


memoryBlocks* init(int n){
    memoryBlocks* mem = (memoryBlocks *)malloc(sizeof(memoryBlocks));
    mem->array = (int*)calloc(sizeof(int)*)

    return mem;
}



int main() {





    return 0;
}