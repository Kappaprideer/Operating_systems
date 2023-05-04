#include <stdlib.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>

#include "common.h"


int main(int arg, char** args){

    int sem_num = atoi(args[1]);
    int sem_id = get_semaphore();

    int shared_memory_id = get_shared_memory();
    barber_shop* salon = shmat(shared_memory_id, NULL, 0);

    struct sembuf sem_info;
    sem_info.sem_num = sem_num;
    sem_info.sem_flg = 0;

    while(TRUE){
        
        sem_info.sem_op = 0;
        semop(sem_id, &sem_info, 1);
        if(salon->free_chairs>0){

            salon->free_chairs--;

            char hairstyle_name[30];
            switch (salon->barber[sem_num])
            {
            case SHORT:
                snprintf(hairstyle_name, 30, "%s", "SHORT");
                break;
            case LONG:
                snprintf(hairstyle_name, 30, "%s", "LONG");
                break;
            case FRESH:
                snprintf(hairstyle_name, 30, "%s", "FRESH");
                break;
            case STYLED:
                snprintf(hairstyle_name, 30, "%s", "STYLED");
                break;
            case NEW_FRESH_STYLED:
                snprintf(hairstyle_name, 30, "%s", "NEW FRESH STYLED");
                break;
            }

            printf("-- BARBER NUM: %d IS DOING: %s \n", sem_num, hairstyle_name);

            sleep(salon->barber[sem_num]);
            
            printf("-- BARBER NUM: %d DONE %s\n", sem_num, hairstyle_name);

            salon->free_barbers++;
            salon->free_chairs++;
            salon->barber[sem_num] = FALSE;

            sem_info.sem_op = 1;
            semop(sem_id, &sem_info, 1);
        }
    }

    return 0;
}