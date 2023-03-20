#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(int arg, char** args){
    if(arg!=2){
        fprintf(stderr, "Wrong number of arguments!\n");
        return EXIT_FAILURE;
    }

    int forks_number = atoi(args[1]);
    pid_t fork_pid;
    
    for(int count=0; count<forks_number; count++){

        fork_pid = fork();

        if(fork_pid == 0){
            printf("Identyfikator procesu macierzysteg: %d Własny identyfikator: %d\n", getppid(), getpid());
            exit(EXIT_SUCCESS);
        }

        if( wait(NULL) == -1 ) perror("Problem with executing wait function!\n");
        
    }

    printf("Liczba procesów: %s\n", args[1]);
    return EXIT_SUCCESS;
}