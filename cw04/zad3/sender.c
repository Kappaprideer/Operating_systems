#define _GNU_SOURCE 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int confirmed = 0;

void handler(int signal_no){
    confirmed=1;
}

int main(int arg, char** args){
    if( arg<3 ){
        fprintf(stderr, "SENDER: Wrong number of arguments");
        return EXIT_FAILURE;
    }

    pid_t catcher_pid = atoi(args[1]);
    struct sigaction action;
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    sigaction(SIGUSR1, &action, NULL);

    int command;
    for(int command_number = 2; command_number < arg; command_number++){
        confirmed = 0;
        command = atoi(args[command_number]);

        if( command < 1 || command > 5 ){
            fprintf(stderr, "Invalid command number: %d!\n", command);
            continue;
        }

        sleep(1);
        
        union sigval signal_number;
        signal_number.sival_int = command;
        sigqueue(catcher_pid, SIGUSR2, signal_number);

        if(confirmed == 0){
            printf("SENDER: Request not confirmed! Seding request again!\n");
            command_number--;
        }
    }

    return 0;
}