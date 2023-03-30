#define _GNU_SOURCE 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>

int change_count = 0;
int quit = 0;
int loop_time = 0;
pid_t sender_pid;

void show_current_time(){
    time_t t;
    time(&t);
    printf("CATCHER: current time is: %s\n",ctime(&t));
}

void print_loop_time(){
    loop_time = 1;
}

void print_hundred(){
    for(int i=1; i<=100; i++) printf("%d ", i);
    printf("\n\n");
}

void show_change_count(){
    printf("CATCHER: Count of change commands: %d\n\n", change_count);
}

void quit_program(){
    printf("CATCHER: Quitting program\n\n");
    quit = 1;
}

void execute_command(int command){
    switch (command) {
    case 1: print_hundred(); break;
    case 2: show_current_time(); break;
    case 3: show_change_count(); break;
    case 4: print_loop_time();  break;
    case 5: quit_program(); break;
    }
}

void read_action(int sig_num, siginfo_t* sig_info, void* nothing){
    change_count++;
    loop_time = 0;
    sender_pid = sig_info->si_pid;
    int command = sig_info->si_value.sival_int;
    execute_command(command);
    kill(sender_pid, SIGUSR1);
}

int main() {

    printf("CATCHER PID: %d\n", getpid());

    struct sigaction action;
    action.sa_sigaction = read_action;
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR2, &action, NULL);
    while(!quit){
        if( loop_time == 1){
            show_current_time();
            sleep(1);
        }
    }
return 0;
}