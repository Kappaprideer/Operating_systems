#include <signal.h>

#include "constants.h"

#define MSG_SIZE sizeof(msgbuf)-sizeof(long)

static int client_num=0;
int s_queue;
int client_id[MAX_CLIENTS];
int active[MAX_CLIENTS];
int c_queue[MAX_CLIENTS];


void handle_init(msgbuf* msg){
    client_num++;
    int i;

    for(i=0; i<MAX_CLIENTS && active[i]==TRUE; i++){}
    if(i==MAX_CLIENTS){
        msg->receiver_id = -1; 
        printf("HERE\n");
    }
    else{
        active[i]=TRUE;
        client_id[i] = client_num;
        c_queue[i]=msg->sender_id;

        msg->receiver_id = client_num;
    }
    printf("Polecial init! ID clienta: %d\n", msg->receiver_id);
    msgsnd(msg->sender_id, msg, MSG_SIZE, 0);
}

void handle_list(msgbuf* msg){
    for(int index=0; index<MAX_CLIENTS; index++){
        if(active[index] == TRUE){
            printf("Client number: %d is active.\n", client_id[index]);
        }
    }
    printf("\n");
}

void handle_to_all(msgbuf* msg){
    for(int i=0; i<MAX_CLIENTS; i++){
        if(active[i] == TRUE && client_id[i]!=msg->sender_id){
            msgsnd(c_queue[i], msg, MSG_SIZE, IPC_NOWAIT);
        }
    }
}

void handle_to_one(msgbuf* msg){
    int index;
    int client = msg->receiver_id;
    for(index=0; index<MAX_CLIENTS && client_id[index]!=client; index++){}
    if(index==MAX_CLIENTS){
        fprintf(stderr, "Wrong client ID!\n");
    }
    else{
        msgsnd(c_queue[index], msg, MSG_SIZE, IPC_NOWAIT);
    }
}


void handle_stop(msgbuf* msg){
    int index;
    for(index=0; index<MAX_CLIENTS; index++){
        if( client_id[index] == msg->sender_id ){
            break;
        }
    }
    active[index] = FALSE;
}

void handle_shutdown(){
    msgbuf* msg = malloc(sizeof(msgbuf));
    msg->type = STOP;

    for(int index=0; index<MAX_CLIENTS; index++){
        if( active[index] == TRUE ){
            msgsnd(c_queue[index], msg, MSG_SIZE, 0);
            msgrcv(s_queue, msg, MSG_SIZE, STOP, 0);
        }
    }
    msgctl(s_queue, IPC_RMID, NULL);
    exit(EXIT_SUCCESS);
}



int main(int arg, char** args){
    for(int i=0; i<MAX_CLIENTS; i++) active[i]=FALSE;

    key_t key = ftok(HOME, SERVER_ID);
    s_queue = msgget(key, IPC_CREAT | 0666);
    if (s_queue == -1){
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    signal(SIGINT, handle_shutdown);

    msgbuf* msg =(msgbuf*)malloc(sizeof(msgbuf)); 

    while(TRUE){

        if(msgrcv(s_queue, msg, MSG_SIZE, -6,0) >=0){
            printf("NEW INFO!\n");
        }
        switch(msg->type) 
        {
            case INIT:
                handle_init(msg);
                break;

            case LIST:
                handle_list(msg);
                break;

            case TO_ALL:
                handle_to_all(msg);
                break;

            case TO_ONE:
                handle_to_one(msg);
                break;

            case STOP:
                handle_stop(msg);
                break;
        }  
    }
    return 0;
}