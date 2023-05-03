#include <stdlib.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>

#include "common.h"

#define BUFF 256

int main(){
    
    key_t sim_key = ftok(SEM_SIMULATION, SIMULATION);
    int sim_sem = semget(sim_key, 1, 0);
    
    key_t client_key = ftok(SEM_CLIENTS, CLIENT);
    int client_sem = semget(client_key, 1, 0);

    char* buffor = calloc(BUFF, sizeof(char));
    size_t size;

    key_t clients_shm_key = ftok(SHM_CLIENTS, CLIENT);
    int client_shm_id = shmget(client_shm_id, 0, IPC_CREAT | 0666);
    
    free(buffor);
    return 0;
}