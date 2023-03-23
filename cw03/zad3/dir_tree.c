#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

size_t size_of_file(FILE *source){
    size_t file_size;
    fseek(source, 0, SEEK_END);
    file_size = ftell(source);
    fseek(source, 0, SEEK_SET);
    return file_size;
}

int check_if_start_with_patter(char *filename, char *pattern)
{
    FILE *file;
    char *buffer;
    file = fopen(filename, "rb");
    size_t file_size = size_of_file(file);

    size_t buffer_size = file_size < strlen(pattern) ? file_size : strlen(pattern);
    buffer = calloc(buffer_size, sizeof(char));

    fread(buffer, sizeof(char), buffer_size, file);

    fclose(file);
    int result = strcmp(buffer, pattern);

    free(buffer);

    return result;
}

int read_directory(char *path, char* pattern){

    DIR *directory;
    struct dirent *file_handler;
    struct stat file_info;
    pid_t fork_pid;

    if (!(directory = opendir(path))){
        fprintf(stderr, "Failed to open directory: %s!\n", path);
        exit(EXIT_FAILURE);
    }

    char* new_path;
    while ((file_handler = readdir(directory)))
    {
        size_t new_path_length = strlen(path) + strlen(file_handler->d_name) + 1;
        if(new_path_length >= PATH_MAX ){
            exit(EXIT_FAILURE);
        }
        size_t path_size = strlen(path);
        new_path=calloc(new_path_length, sizeof(char));

        for(size_t index=0; index<path_size; index++) new_path[index] = path[index];
        new_path[path_size]='/';
        for(size_t index=path_size+1; index<new_path_length; index++) new_path[index] = file_handler->d_name[index - path_size - 1];


        if (stat(new_path, &file_info) == -1){
            continue;
        }
        else if (S_ISDIR(file_info.st_mode))
        {
            if (strcmp(file_handler->d_name, ".") != 0 && strcmp(file_handler->d_name, "..") != 0)
            {
                fork_pid = fork();
                if(fork_pid == 0 ){
                    read_directory(new_path, pattern);
                }

                if (wait(NULL) == -1){
                    perror("Problem with executing wait function!\n");
                    closedir(directory);
                    free(new_path);
                    new_path=NULL;
                    exit(EXIT_FAILURE);
                }
            }
            free(new_path);
        }
        else
        {
            if (check_if_start_with_patter(new_path, pattern) == 0 )
            {
                printf("Path: %s PID: %d\n", new_path, getpid());
                fflush(stdout);
            }
            free(new_path);
            new_path=NULL;
        }
    }
    if (closedir(directory)){
        perror("Failed to close directory!\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}

int main(int arg, char **args)
{
    if (arg != 3){
        fprintf(stderr, "Wrong number of arguments!\n");
        return EXIT_FAILURE;
    }

    pid_t fork_pid = fork();
    if(fork_pid == 0) read_directory(args[1], args[2]);
    if (wait(NULL) == -1){
        perror("Problem with executing wait function!\n");
        return 1;
    }
    return 0;
}