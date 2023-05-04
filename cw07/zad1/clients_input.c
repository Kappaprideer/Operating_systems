#include <stdlib.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>


#include "common.h"

#define READ_BUFFOR 256

static int client_num = 0;
char* buffor;

void sigint_handler(){
    free(buffor);
    printf("\nQUITTING...\n");
    exit(0);
}

void add_client_to_queue(barber_shop* salon, int hairstyle){
    salon->new_client = ++client_num;
    salon->new_hairstyle = hairstyle;
}

int main(){
    signal(SIGINT, sigint_handler);

    int shared_memory_id = get_shared_memory();
    barber_shop* barber_shop = shmat(shared_memory_id, NULL, 0);

    buffor = calloc(READ_BUFFOR, sizeof(char));
    size_t size;


    while(TRUE){
        if(strcmp(buffor,"QUIT\n") == 0) sigint_handler();
        
        getline(&buffor, &size, stdin);

        int hairstyle = -1;

        if(strcmp(buffor, "SHORT\n") == 0){
            hairstyle = SHORT;
        }
        else if(strcmp(buffor, "LONG\n") == 0){
            hairstyle = LONG;
        }
        else if(strcmp(buffor, "FRESH\n") == 0){
            hairstyle = FRESH;
        }
        else if(strcmp(buffor, "STYLED\n") == 0){
            hairstyle = STYLED;
        }
        else if(strcmp(buffor, "NEW FRESH STYLED\n") == 0){
            hairstyle = NEW_FRESH_STYLED;
        }
        else{ fprintf(stderr, "Invalid hairstyle. Try again!\n"); }

        if(hairstyle != -1){
            if(barber_shop->currently_in_queue < MAX_QUEUE){
                add_client_to_queue(barber_shop, hairstyle);
            }
            else printf("Sorry, there is no space in queue.\n");
        }
    }

    free(buffor);
    return 0;
}