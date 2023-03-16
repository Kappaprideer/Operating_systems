#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BLOCK_SIZE 1024

long long size_of_file(FILE* file){
    long long file_size;
    fseek(file, 0, SEEK_END);
    file_size =  ftell(file);
    fseek(file, 0, SEEK_SET);
    return file_size;
}

void change_letters(char* text, char begin, char end){
    for(long long index=0; index<strlen(text); index++){
        if(text[index] == begin){
            text[index] = end;
        }
    }
}

void library_function(char** args){
    FILE *source, *destiny;
    char* buffer;

    source = fopen(args[3],"rb");
    long long file_size = size_of_file(source);
    buffer = calloc(sizeof(char), file_size);

    size_t index = 0 ;
    while (index<file_size) {
        size_t bytes_to_read = (file_size-index < BLOCK_SIZE) ? file_size-index : BLOCK_SIZE;
        index += fread(&buffer[index], sizeof(char), bytes_to_read, source);
    }

    change_letters(buffer,args[1][0],args[2][0]);
    destiny = fopen(args[4], "wb");
    fwrite(buffer,sizeof(char), file_size,destiny);
    free(buffer);
    fclose(destiny);
    fclose(source);
}

void system_function(char** args){
    int source, destiny;
    source = open(args[3], O_RDONLY);
    destiny = open(args[4], O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR);

    char c;
    while(read(source,&c,1)==1) {
        if(c==args[1][0]){
            c=args[2][0];
        }
        write(destiny, &c, 1);
    }

    close(source);
    close(destiny);
}

int main(int arg, char** args){
    if(arg!=5){
        fprintf(stderr, "Invalid count of arguments!\n");
        return 1;
    }

    struct timespec lib_start, lib_end, sys_start, sys_end;

    clock_gettime(CLOCK_MONOTONIC, &lib_start);
    library_function(args);
    clock_gettime(CLOCK_MONOTONIC, &lib_end);

    clock_gettime(CLOCK_MONOTONIC, &sys_start);
    system_function(args);
    clock_gettime(CLOCK_MONOTONIC, &sys_end);

    printf("Time for functions from libraries: %ld ns\n", lib_end.tv_nsec-lib_start.tv_nsec);
    printf("Time for system functions: %ld ns\n", sys_end.tv_nsec-sys_start.tv_nsec);
    return 0;
}