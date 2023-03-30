#define _GNU_SOURCE 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

struct sigaction action;


void read_siginfo(int sig_num, siginfo_t* sig_info, void* nothing){
    printf("Signal number: %d\n", sig_info->si_signo);
    printf("PID: %d\n",sig_info->si_pid);
    printf("Signal code: %d\n", sig_info->si_code);
    printf("Errno value associated with this signal: %d\n", sig_info->si_errno);
    printf("Exit value or signal for process termination: %d\n", sig_info->si_status);
}

void test_siginfo(){
    action.sa_flags = SA_SIGINFO;
    action.sa_sigaction = read_siginfo;
    sigaction(SIGUSR1, &action, NULL);

    printf("\nSIGINFO FLAG:\n");
    raise(SIGUSR1);
}



void test_oneshot(){
    action.sa_flags = SA_ONESHOT;
    action.sa_sigaction = read_siginfo;
    sigaction(SIGUSR1, &action, NULL);

    printf("\n\nONESHOT FLAG:\n");
    raise(SIGUSR1);
    printf("\nNOW SIGUSR WORK LIKE DEFAULT:\n");
    fflush(stdout);
    raise(SIGUSR1);
}

int main() {
    sigemptyset(&action.sa_mask);

    test_siginfo();

    test_oneshot();

    return 0;
}