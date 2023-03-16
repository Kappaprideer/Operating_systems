#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define BLOCK_SIZE 1024

long long size_of_file(FILE* file){
    long long file_size;
    fseek(file, 0, SEEK_END);
    file_size =  ftell(file);
    fseek(file, 0, SEEK_SET);
    return file_size;
}

void library_function(int arg, char** args){
    FILE *source, *destiny;
    char argument, change_to;
    char* buffer;
    argument = args[1][0];
    change_to = args[2][0];

    source = fopen(args[3],"rb");
    long long file_size = size_of_file(source);
    buffer = calloc(sizeof(char), file_size);
    size_t index = 0 ;
    while (index<file_size) {
        size_t bytes_to_read = (file_size-index < BLOCK_SIZE) ? file_size-index : BLOCK_SIZE;
        index += fread(&buffer[index], sizeof(char), bytes_to_read, source);
    }
    for(long long index=0; index<file_size; index++){
        if(buffer[index] == argument){
            buffer[index] = change_to;
        }
    }
    destiny = fopen(args[4], "wb");
    fwrite(buffer,sizeof(char), file_size,destiny);
    free(buffer);
    fclose(destiny);
    fclose(source);
}




int main(int arg, char** args){
    if(arg!=5){
        fprintf(stderr, "Invalid count of arguments!\n");
        return 1;
    }





    
    return 0;
}