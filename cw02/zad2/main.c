#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>

#define BUFFER_SIZE 1024
#define BLOCK_SIZE 1024



// reading_variant - dla 0 - wczytywanie znak po znaku
// reading_variant - dla 1 - wczytywnaie po 1024 znaki
void reverse(FILE* one, FILE* two, int reading_variant){
    
    char buffer[BUFFER_SIZE];
    long file_size;
    fseek(one, 0, SEEK_END);
    file_size = ftell(one);
    fseek(one, 0, SEEK_SET);

    if(reading_variant==0){
        while (file_size > 0) {
            size_t bytes_to_read = (file_size < BUFFER_SIZE) ? file_size : BUFFER_SIZE;
            fread(buffer, 1, bytes_to_read, one);

            for (int i = bytes_to_read - 1; i >= 0; i--) {
                fputc(buffer[i], two);
            }

            file_size -= bytes_to_read;
        }
    }
    else{




    }
}




int main(int argc, char* arguments[]) {
    
    char* filename_one = arguments[1];
    // char* filename_two = arguments[2];

    FILE *source_file, *dest_file;

    source_file = fopen(filename_one, "rb");
    dest_file = fopen(, "wb");

    if (source_file == NULL || dest_file == NULL) {
        fprintf(stderr, "Can't open the file!\n");
        exit(1);
    }

    struct timespec start, end, blocks_start, blocks_end;

    clock_gettime(CLOCK_MONOTONIC, &start);
    reverse(source_file, dest_file, 0);
    clock_gettime(CLOCK_MONOTONIC, &end);

    clock_gettime(CLOCK_MONOTONIC, &blocks_start);
    reverse(source_file, dest_file, 1);
    clock_gettime(CLOCK_MONOTONIC, &blocks_end);

    fclose(source_file);
    fclose(dest_file);

    printf("Reading each char time: %ld ns\n", end.tv_nsec-start.tv_nsec);
    printf("Reading blocks of chars time: %ld ns\n", blocks_end.tv_nsec-blocks_start.tv_nsec);
    
    return 0;
}