#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>

// #define BUFFER_SIZE 1024
#define BLOCK_SIZE 1024


// reading_variant - dla 0 - wczytywanie znak po znaku
// reading_variant - dla 1 - wczytywnaie po 1024 znaki
void reverse(FILE* one, int reading_variant){
    
    FILE* dest_file;
    char* buffer;
    long file_size;




    fseek(one, 0, SEEK_END);
    file_size = ftell(one);
    size_t begin_point = (file_size<BLOCK_SIZE) ? 0 : (file_size - BLOCK_SIZE);
    fseek(one, 0, SEEK_SET);

    if(reading_variant==0){
        dest_file = fopen("reversed_char.txt", "wb");

        while (file_size > 0) {
            size_t bytes_to_read = 1;
            fread(buffer, 1, bytes_to_read, one);
            
            for (int i = bytes_to_read - 1; i >= 0; i--) {
                if(fputc(buffer[i], dest_file) != (int)(buffer[i])){
                    printf("BŁAD W CHAR");
                }
            }
            file_size -= bytes_to_read;
        }
    }

    else{
        dest_file = fopen("reversed_block.txt", "wb");

        while (file_size > 0) {
            size_t bytes_to_read = (file_size < BLOCK_SIZE) ? file_size : BLOCK_SIZE;
            fread(buffer, 1, bytes_to_read, one);
            for (int i = bytes_to_read - 1; i >= 0; i--) {
                if(fputc(buffer[i], dest_file) != (int)buffer[i]){
                    printf("PROBLEM\n");
                }
            }
            file_size -= bytes_to_read;
        }
    }
    fclose(dest_file);
}




int main(int argc, char* arguments[]) {
    
    char* filename_one = arguments[1];
    FILE *source_file;

    source_file = fopen(filename_one, "rb");

    if (source_file == NULL) {
        fprintf(stderr, "Can't open the file!\n");
        exit(1);
    }

    struct timespec start, end, blocks_start, blocks_end;

    clock_gettime(CLOCK_MONOTONIC, &start);
    reverse(source_file, 0);
    clock_gettime(CLOCK_MONOTONIC, &end);

    clock_gettime(CLOCK_MONOTONIC, &blocks_start);
    reverse(source_file, 1);
    clock_gettime(CLOCK_MONOTONIC, &blocks_end);

    fclose(source_file);

    printf("Reading each char time: %ld ns\n", end.tv_nsec-start.tv_nsec);
    printf("Reading blocks of chars time: %ld ns\n", blocks_end.tv_nsec-blocks_start.tv_nsec);
    
    return 0;
}