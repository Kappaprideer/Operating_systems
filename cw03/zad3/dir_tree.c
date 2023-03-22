#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



size_t size_of_file(FILE* source){
    size_t file_size;
    fseek(source, 0, SEEK_END);
    file_size = ftell(source);
    fseek(source,0,SEEK_SET);
    return file_size;
}


int check_if_start_with_patter(char* filename, char* pattern){
    FILE* file;
    char* buffer;
    file = fopen(filename,"rb");
    size_t file_size = size_of_file(file);

    size_t buffer_size = min(file_size, strlen(pattern));

    fread(buffer, sizeof(char), buffer_size, file);

    fclose(file);

    if( strcmp(buffer, pattern) == 0){
        return 0;
    }
    return 1;
}

int read_directory(char* path, char* pattern){
    DIR* directory;
    struct dirent* file_handler;
    struct stat file_info;

    if( !(directory = opendir(path)) ){ 
        perror("Failed to open directory!\n"); 
        exit(EXIT_FAILURE);    
    }

    pid_t fork_pid;
    char* new_path;

    while((file_handler = readdir(directory))){
    
        if( stat(file_handler->d_name, &file_info) != 0 ){
            fprintf("Failed to read info about %s!\n", file_handler->d_name);
            continue;
        }

        if(S_ISDIR(file_info.st_mode)){
            if( strcmp(file_handler->d_name,".") != 0 && strcmp(file_handler->d_name,"..") != 0 ){
                // stworzyć nową nazwę ścieżki do pliku
                fork_pid = fork();

                read_directory(new_path, pattern);
                
                if( wait(NULL) == -1 ) perror("Problem with executing wait function!\n");

            }    
        }
        else{
            if( check_if_start_with_patter(file_handler->d_name, pattern) == 0 ){
            //wypisac cala sciezke pliku
            printf("Size: %ld Filename: %s\n", file_info.st_size ,file_handler->d_name);
            // printf();
        }

    exit(EXIT_SUCCESS);
    }
}




int main(int arg, char** args){
    if(args!=3){
        fprintf(stderr, "Wrong number of arguments!\n");
        return EXIT_FAILURE;
    }


    DIR* directory;
    struct dirent* file_handler;
    struct stat file_info;
        

    if(!(directory = opendir(args[1]))){ 
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


        }
        else{
            printf();
        }
    
    
    
    
    }


    if(closedir(directory)){
        fprintf(stderr, "Failed to close directory!\n");
        exit(EXIT_SUCCESS);
    }
    
    
    
    return 0;
}