#include <stdlib.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#include "common.h"

int shm_id, sem_id, barbers[MAX_BARBERS];

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};

void sigint_handler(){
    shmctl(shm_id, IPC_RMID, NULL);
    for(int index=0; index<MAX_BARBERS; index++){
        kill(SIGINT, barbers[index]);
    }
    semctl(sem_id, 0, IPC_RMID, NULL);
    
    printf("\nQUITTING...\n");
    exit(0);
}

void print_info(barber_shop* salon){
    printf("Number of free chairs: %d\n", salon->free_chairs);
    printf("Number of free barbers: %d\n", salon->free_barbers);
    printf("Number of people in queue: %d\n", salon->currently_in_queue);
    printf("\n-----------------------------------------\n");
    printf("Available haircuts: \nSHORT - 2s\nLONG-7s\nFRESH - 9s\nSTYLED - 10s\nNEW FRESH STYLED - 11s");
    printf("\n-----------------------------------------\n\n");
}

int create_shared_memory(){
    
    key_t key = ftok(SHM_SIMULATION, SIMULATION);

    int shared_memory_id = shmget(key, SIZE, IPC_CREAT | 0666);
    
    if (shared_memory_id < 0){
        fprintf(stderr, "Can't create shared memory!\n");
        exit(EXIT_FAILURE);
    }

    barber_shop* barber_shop = shmat(shared_memory_id, NULL, 0);
    barber_shop->new_client = FALSE;
    barber_shop->currently_in_queue = 0;
    barber_shop->queue_at = 0;
    barber_shop->free_barbers = MAX_BARBERS;
    barber_shop->free_chairs = MAX_CHAIRS;

    for(int index = 0; index<MAX_QUEUE; index++)    barber_shop->queue[index] = FALSE;
    for(int index = 0; index<MAX_BARBERS; index++)    barber_shop->barber[index] = FALSE;
    // for(int index = 0; index<MAX_CHAIRS; index++)    barber_shop->chairs[index] = FALSE;

    return shared_memory_id;
}

int create_semaphore(){
    key_t sem_key = ftok(SEM_SIMULATION, SIMULATION);

    int semaphore_id = semget(sem_key, MAX_BARBERS, IPC_CREAT | 0666);
    if (semaphore_id < 0){
        printf("Cannot create semaphores set\n");
        exit(EXIT_FAILURE);
    }
    
    union semun arg;    
    arg.val = 1;
    for(int index=0; index<MAX_BARBERS; index++)
        semctl(semaphore_id, index, SETVAL, arg);

    return semaphore_id;
}

void set_barbers(){
    for(int index = 0; index<MAX_BARBERS; index++){
        int child = fork();
        if (child == 0){
            char buff[5];
            snprintf(buff, 5, "%d", index);
            execl("./barber", "barber", buff, NULL);
        }
        barbers[index] = child;
    }
}


int main(){

    sem_id = create_semaphore();

    shm_id = create_shared_memory();
    barber_shop* barber_shop = shmat(shm_id, NULL, 0);

    set_barbers();
    
    signal(SIGINT, sigint_handler);
    
    print_info(barber_shop);

    while(TRUE){

        if(barber_shop->new_client != FALSE){
            printf("CLIENT NUM: %d GOES TO QUEUE\n", barber_shop->new_client);
            
            if(barber_shop->free_barbers>0 && barber_shop->currently_in_queue<MAX_QUEUE){
                for(int index=0; index<MAX_BARBERS; index++){
                    if(barber_shop->barber[index] == FALSE){
                        barber_shop->free_barbers--;
                        barber_shop->barber[index] = barber_shop->new_hairstyle;

                        if(barber_shop->free_chairs <= 0){
                            barber_shop->currently_in_queue++;
                        }

                        struct sembuf sem_info;
                        sem_info.sem_num = index;
                        sem_info.sem_op = -1;
                        sem_info.sem_flg = 0;
                        semop(sem_id, &sem_info, 1);
                        break;
                    }
                }
            }
            else{
                printf("CLIENT NUM: %d GOES TO QUEUE\n", barber_shop->new_client);
                barber_shop->currently_in_queue++;
                barber_shop->queue[barber_shop->queue_at] = barber_shop->new_hairstyle;
                barber_shop->queue_at = (barber_shop->queue_at+1)%MAX_QUEUE;
            }
            barber_shop->new_client = FALSE;
        }
    }
}