#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_BARBERS 5
#define MAX_CHAIRS 3
#define MAX_QUEUE 2

#define SIMULATION 0

#define SEM_SIMULATION "/tmp/simulation_sem"

#define SHM_SIMULATION "/tmp/simulatin_shm"

#define FALSE 0
#define TRUE 1

#define SHORT 4
#define LONG 5
#define FRESH 6
#define STYLED 7
#define NEW_FRESH_STYLED 30

#define SIZE sizeof(barber_shop)

typedef struct{

    int new_client;
    int new_hairstyle;

    int currently_in_queue;
    int queue_at;

    int free_barbers;
    int barber_index;
    int free_chairs;

    int queue[MAX_QUEUE+MAX_BARBERS];
    int barber[MAX_BARBERS];
    
} barber_shop;

int get_semaphore();
int get_shared_memory();

#endif