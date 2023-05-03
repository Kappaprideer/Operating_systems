#include <stdlib.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

#include "common.h"

int free_chairs = MAX_CHAIRS, free_barbers = MAX_BARBERS, queue = 0;

void print_info(){
    printf("Number of free chairs: %d\n", free_chairs);
    printf("Number of free barbers: %d\n", free_barbers);
    printf("Number of people in queue: %d\n", queue);
    printf("\n-----------------------------------------\n");
    printf("Available haircuts: \nSHORT - 2s\nLONG-7s\nFRESH - 9s\nSTYLED - 10s\nNEW FRESH STYLED - 11s");
    printf("\n-----------------------------------------\n\n");
}


int main(){

    key_t sim_key = ftok(SEM_SIMULATION, SIMULATION);
    int sim_sem = semget(sim_key, 1, IPC_CREAT | 0666);

    key_t barber_key = ftok(SEM_BARBERS, BARBER);
    int barber_sem = semget(barber_key, 1, IPC_CREAT | 0666);

    key_t client_key = ftok(SEM_CLIENTS, CLIENT);
    int client_sem = semget(client_key, 1, IPC_CREAT | 0666);

    print_info();
    
    while(1){
        





    }
}