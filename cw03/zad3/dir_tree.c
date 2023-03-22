#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
    buffer = malloc(sizeof(char)*buffer_size);

    fread(buffer, sizeof(char), buffer_size, file);

    fclose(file);
    free(buffer);

    return strcmp(buffer, pattern);
}


int read_directory(char *path, char *pattern){

    DIR *directory;
    struct dirent *file_handler;
    struct stat file_info;

    if (!(directory = opendir(path))){
        perror("Failed to open directory!\n");
        exit(EXIT_FAILURE);
    }

    pid_t fork_pid;

    while ((file_handler = readdir(directory)))
    {

        if (stat(file_handler->d_name, &file_info) != 0)
        {
            fprintf(stderr, "Failed to read info about %s!\n", file_handler->d_name);
            closedir(directory);
            exit(EXIT_FAILURE);
        }

        if (S_ISDIR(file_info.st_mode))
        {
            if (strcmp(file_handler->d_name, ".") != 0 && strcmp(file_handler->d_name, "..") != 0)
            {
                // stworzyć nową nazwę ścieżki do pliku
                size_t new_path_length = strlen(path) + strlen(file_handler->d_name) + 1;
                size_t path_size = strlen(path);

                char new_path[new_path_length];
                for(int index=0; index<path_size; index++) new_path[index] = path[index];
                new_path[path_size]='/';
                for(int index=path_size+1; index<path_size; index++) new_path[index] = file_handler->d_name[index];

                fork_pid = fork();

                read_directory(new_path, pattern);

                if (wait(NULL) == -1){
                    perror("Problem with executing wait function!\n");
                    closedir(directory);
                    exit(EXIT_FAILURE);
                }
            }
        }
        else
        {
            if (check_if_start_with_patter(file_handler->d_name, pattern) == 0)
            {
                // wypisac cala sciezke pliku
                printf("Size: %ld Filename: %s\n", file_info.st_size, file_handler->d_name);
            }
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
    if (arg != 3)
    {
        fprintf(stderr, "Wrong number of arguments!\n");
        return EXIT_FAILURE;
    }

    pid_t fork_pid = fork();
    read_directory(args[1],args[2]);
    if (wait(NULL) == -1){
        perror("Problem with executing wait functoin!\n");
        return 1;
    }

    return 0;
}