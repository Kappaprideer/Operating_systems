#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void revstr(char* string)  
{  
    int i, length, temp;  
    length = strlen(string); 
      
    for (i = 0; i < length/2; i++)  {  
        temp = string[i];  
        string[i] = string[length - i - 1];  
        string[length - i - 1] = temp;  
    }  
}


// reading_variant - dla 0 - wczytywanie znak po znaku
// reading_variant - dla 1 - wczytywnaie po 1024 znaki
void reverse(FILE* one, int reading_variant){
    
    int BLOCK_SIZE = (reading_variant==0) ? 1 : 1024;
    FILE* dest_file;
    char* buffer;
    size_t file_size;

    fseek(one, 0, SEEK_END);
    file_size = ftell(one);
    fseek(one, 0, SEEK_SET);

    buffer = calloc(file_size, sizeof(char));

    size_t index = 0 ;
    while (index<file_size) {
        size_t bytes_to_read = (file_size-index < BLOCK_SIZE) ? file_size-index : BLOCK_SIZE;
        index += fread(&buffer[index], sizeof(char), bytes_to_read, one);
    }

    revstr(buffer);

    char* dest_file_name = (reading_variant==0) ? "reversed_char.txt" : "reversed_block.txt";
    
    dest_file = fopen(dest_file_name, "wb");
    fwrite(buffer, 1, file_size, dest_file);
    
    fclose(dest_file);
    
    free(buffer);
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


    // while (file_size > 0) {
    //     size_t bytes_to_read = (file_size < BLOCK_SIZE) ? file_size : BLOCK_SIZE;
    //     fread(buffer, 1, bytes_to_read, one);
    //     for (int i = bytes_to_read - 1; i >= 0; i--) {
    //         if(fputc(buffer[i], dest_file) != (int)buffer[i]){
    //             printf("PROBLEM\n");
    //         }
    //     }
    //     file_size -= bytes_to_read;
    // }