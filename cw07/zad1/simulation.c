#include <stdlib.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>


#include "common.h"

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};


int free_chairs = MAX_CHAIRS, free_barbers = MAX_BARBERS, queue = 0;

void print_info(){
    printf("Number of free chairs: %d\n", free_chairs);
    printf("Number of free barbers: %d\n", free_barbers);
    printf("Number of people in queue: %d\n", queue);
    printf("\n-----------------------------------------\n");
    printf("Available haircuts: \nSHORT - 2s\nLONG-7s\nFRESH - 9s\nSTYLED - 10s\nNEW FRESH STYLED - 11s");
    printf("\n-----------------------------------------\n\n");
}

int create_shared_memory(int type){
    key_t key;
    switch (type){

    case SIMULATION:
        key = ftok(SHM_SIMULATION, SIMULATION);
        break;
    
    case CLIENT:
        key = ftok(SHM_CLIENTS, CLIENT);
        break;    
    }

    int shared_memory_id = shmget(key, SIZE, IPC_CREAT | 0666);
    
    if (shared_memory_id < 0){
        fprintf(stderr, "Can't create shared memory!\n");
        exit(EXIT_FAILURE);
    }
    return shared_memory_id;
}

int create_semaphore(int type){
    key_t sem_key;

    switch (type){
        case SIMULATION:
            sem_key = ftok(SEM_SIMULATION, SIMULATION);
            break;    
        case BARBER:
            sem_key = ftok(SEM_BARBERS, BARBER);
            break;
        case CLIENT:
            sem_key = ftok(SEM_CLIENTS, CLIENT);
            break;    
    }

    int semaphore_id = semget(sem_key, 1, IPC_CREAT | 0666);
    if (semaphore_id < 0){
        printf("Cannot create semaphores set\n");
        exit(EXIT_FAILURE);
    }
    
    union semun arg;    
    arg.val = 0;
    semctl(semaphore_id, 0, SETVAL, arg);
    
    return semaphore_id;
}



int main(){

    int sim_sem = create_semaphore(SIMULATION);
    int barber_sem = create_semaphore(BARBER);
    int client_sem = create_semaphore(CLIENT);

    int client_shm_id = create_shared_memory(CLIENT);

    print_info();
    
    while(1){






    }
}