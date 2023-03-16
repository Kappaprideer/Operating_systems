#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(){

    DIR* directory;
    struct dirent* file_handler;
    struct stat file_info;
    long long sizes_sum = 0;
    
    if(!(directory = opendir("."))){ 
        fprintf(stderr, "Failed to open directory!\n"); 
        return 1;    
    }

    while((file_handler = readdir(directory))){
    
        if( stat(file_handler->d_name, &file_info)){
            fprintf(stderr, "Failed to read info about %s!\n", file_handler->d_name);
            continue;
        }

        if(!S_ISDIR(file_info.st_mode)){
            printf("Size: %ld Filename: %s\n", file_info.st_size ,file_handler->d_name);
            sizes_sum += file_info.st_size;
        }
    }

    if(closedir(directory)){
        fprintf(stderr, "Failed to close directory!\n");
        return 1;
    }
    printf("Total size of files: %lld\n", sizes_sum);

    return 0;
}