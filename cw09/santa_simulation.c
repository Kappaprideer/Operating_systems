#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

#define TRUE 1
#define ELFS_COUNT 10
#define REINDEER_COUNT 9

int elfs_waiting=0, reindeer_waiting=0, gifts_delivered=0;
pthread_t *elfs, *santa_clause, *reindeers;

pthread_mutex_t elfs_waiting_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t reindeer_waiting_mutex = PTHREAD_MUTEX_INITIALIZER;


pthread_cond_t wake_up_santa = PTHREAD_COND_INITIALIZER;

pthread_cond_t elfs_problem_solved = PTHREAD_COND_INITIALIZER;
pthread_cond_t reindeer_gifts_delivered = PTHREAD_COND_INITIALIZER;

unsigned long elfs_queue[3];


void* santa(void* arg){
    while(TRUE){
        
        pthread_mutex_lock(&elfs_waiting_mutex);
        while( elfs_waiting < 3 && reindeer_waiting < REINDEER_COUNT){
            pthread_cond_wait(&wake_up_santa, &elfs_waiting_mutex);
        }
        printf("Mikolaj: budze sie\n");
        pthread_mutex_lock(&reindeer_waiting_mutex);

        if(elfs_waiting == 3){
            printf("Mikołaj: rozwiązuje problemy elfów: %ld, %ld, %ld\n", elfs_queue[0], elfs_queue[1], elfs_queue[2]);

            pthread_mutex_unlock(&elfs_waiting_mutex);
            sleep(rand()%2 + 1);
            pthread_mutex_lock(&elfs_waiting_mutex);

            elfs_waiting = 0;
            pthread_cond_broadcast(&elfs_problem_solved);
        }
        if(reindeer_waiting == REINDEER_COUNT){
            printf("Mikołaj: dostarczam zabawki\n");
            sleep(rand()%3 + 2);
            reindeer_waiting = 0;
            gifts_delivered++;
            pthread_cond_broadcast(&reindeer_gifts_delivered);
        }
        printf("Mikolaj: Zasypiam\n");
        pthread_mutex_unlock(&elfs_waiting_mutex);
        pthread_mutex_unlock(&reindeer_waiting_mutex);
    }
    return NULL;
}



void* elf(void* arg){

    while(TRUE){
        int work_duration = rand()%4 + 2;
        sleep(work_duration);
        
        pthread_mutex_lock(&elfs_waiting_mutex);

        if(elfs_waiting<3){
            elfs_queue[elfs_waiting]=pthread_self();
            elfs_waiting++;
            printf("ELF: Czeka %d elfów na mikołaja, ID: %ld\n", elfs_waiting, pthread_self());

            if(elfs_waiting == 3) {
                printf("Elf: wybudzam mikołaja, ID: %ld\n", pthread_self());
                pthread_cond_broadcast(&wake_up_santa);
                printf("Elf: Mikolaj rozwiazuje problem\n");
            }

            pthread_cond_wait(&elfs_problem_solved, &elfs_waiting_mutex);
        }
        else{
            printf("Elf: samodzielnie rozwiazuje swoj problem, ID: %ld\n", pthread_self());
        }
        pthread_mutex_unlock(&elfs_waiting_mutex);
    }
    return NULL;
}



void* reindeer(void* arg){

    while(TRUE){
        int holidays_duration = rand()%6+ 5;
        sleep(holidays_duration);

        pthread_mutex_lock(&reindeer_waiting_mutex);
        reindeer_waiting++;
        printf("Renifer: czeka %d reniferów na Mikołaja, ID: %ld \n", reindeer_waiting, pthread_self());
        if(reindeer_waiting == REINDEER_COUNT){
            printf("Renifer: wybudzam Mikołaja, ID: %ld \n", pthread_self());
            pthread_cond_broadcast(&wake_up_santa);
        }
        pthread_cond_wait(&reindeer_gifts_delivered, &reindeer_waiting_mutex);

        pthread_mutex_unlock(&reindeer_waiting_mutex);
    }
    return NULL;
}




void create_threads_and_allocate_memory();

void kill_threads_and_free_memory();


int main(int arg, char** args){
    if(arg != 1){
        fprintf(stderr, "Invalid number of arguments!\n");
        return -1;
    }

    signal(SIGINT, kill_threads_and_free_memory);

    create_threads_and_allocate_memory();    

    while(gifts_delivered < 3){
        sleep(0.5);
    }

    kill_threads_and_free_memory();

    return 0;
}


void create_threads_and_allocate_memory(){
    santa_clause = calloc(1, sizeof(pthread_t));
    elfs = calloc(ELFS_COUNT, sizeof(pthread_t));
    reindeers = calloc(REINDEER_COUNT, sizeof(pthread_t));
    
    if(pthread_create(santa_clause, NULL, santa, NULL) != 0){
        fprintf(stderr, "Problem with creating santaclaus thread!\n");
        exit(-1);
    }

    for(int i=0; i<ELFS_COUNT; i++){
        if(pthread_create(elfs+i, NULL, elf, NULL) != 0){
            fprintf(stderr, "Problem with creating elf thread!\n");
            exit(-1);
        }
    }

    for(int i=0; i<REINDEER_COUNT; i++){
        if(pthread_create(reindeers+i, NULL, reindeer, NULL) != 0){
            fprintf(stderr, "Problem with creating reindeer thread!\n");
            exit(-1);
        }
    }
}

void kill_threads_and_free_memory(){
    
    // pthread_cancel(*santa_clause);
    // for(int index=0; index<ELFS_COUNT; index++){
    //     if(pthread_cancel(elfs[index]) != 0) fprintf(stderr, "Problem with canceling elf thread!\n");
    // }

    // for(int index=0; index<9; index++){
    //     if(pthread_cancel(reindeers[index]) != 0) fprintf(stderr, "Problem with canceling reindeers thread!\n");
    // }

    free(elfs);
    free(santa_clause);
    free(reindeers);

    exit(EXIT_SUCCESS);
}



