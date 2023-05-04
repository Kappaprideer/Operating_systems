#include "common.h"

int get_semaphore(){
    key_t key = ftok(SEM_SIMULATION, SIMULATION);
    
    int semaphore_id = semget(key, 0, 0);
    if (semaphore_id < 0){
        fprintf(stderr, "Cant' reach remaphore!\n");
        exit(EXIT_FAILURE);
    }
    return semaphore_id;
}

int get_shared_memory(){

    key_t key = ftok(SHM_SIMULATION, SIMULATION);

    int shared_memory_id = shmget(key, 0, 0);

    if (shared_memory_id < 0){
        fprintf(stderr, "Can't reach shared memory!!\n");
        exit(EXIT_FAILURE);
    }
    return shared_memory_id;
}