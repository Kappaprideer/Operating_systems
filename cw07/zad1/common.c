#include <stdlib.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>

#include <common.h>

int get_semaphore(int type){
    key_t key;

    switch (type){
        case SIMULATION:
            key = ftok(SEM_SIMULATION, SIMULATION);
            break;    
        case BARBER:
            key = ftok(SEM_BARBERS, BARBER);
            break;
        case CLIENT:
            key = ftok(SEM_CLIENTS, CLIENT);
            break;    
    }

    int semaphore_id = semget(key, 0, 0);
    if (semaphore_id < 0){
        fprintf(stderr, "Cant' reach remaphore!");
        exit(EXIT_FAILURE);
    }
    return semaphore_id;
}

int get_shared_memory(int type){

    key_t key;
    switch (type){
        case SIMULATION:
            key = ftok(SHM_SIMULATION, SIMULATION);
            break;
        case CLIENT:
            key = ftok(SHM_CLIENTS, CLIENT);
            break;    
    }

    
    int shared_memory_id = shmget(key, 0, 0);

    if (shared_memory_id < 0){
        fprintf(stderr, "Can't reach shared memory!!\n");
        exit(EXIT_FAILURE);
    }
    return shared_memory_id;
}