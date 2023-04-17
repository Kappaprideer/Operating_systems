#include <signal.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"

#define LINE_LEN 1024
#define MSG_SIZE sizeof(msgbuf) - sizeof(long)
char* line;
int client_id, queue_id, server_id;

void init(){    
    msgbuf* msg = malloc(sizeof(msgbuf));
    msg->type = INIT;
    msg->sender_id = queue_id;
    msgsnd(server_id, msg, MSG_SIZE, 0);
    msgrcv(queue_id, msg, MSG_SIZE, INIT, INIT);

    if (( client_id = msg->receiver_id) == -1){
        fprintf(stderr, "No free slots for new client!\n");
        exit(EXIT_SUCCESS);
    }
    // free(msg);
}

void list_handler(){
    msgbuf* msg =(msgbuf*)malloc(sizeof(msgbuf));
    msg->type = LIST;
    msg->sender_id = client_id;
    msgsnd(server_id, msg, MSG_SIZE, 0);
}

void to_all_handler(char* message){
    msgbuf* msg =(msgbuf*)malloc(sizeof(msgbuf));

    msg->type = TO_ALL;
    msg->sender_id = client_id;
    strcpy(msg->text, message);

    msgsnd(server_id, msg, MSG_SIZE, 0);
}

void to_one_handler(int receiver_id, char* message){
    msgbuf* msg =(msgbuf*)malloc(sizeof(msgbuf));

    msg->type = TO_ONE;
    msg->sender_id = client_id;
    msg->receiver_id = receiver_id;
    strcpy(msg->text, message);

    msgsnd(server_id, msg, MSG_SIZE, 0);
}

void stop_handler(){
    msgbuf* msg =(msgbuf*)malloc(sizeof(msgbuf));
    msg->type = STOP;
    msg->sender_id = client_id;
    msgsnd(server_id, msg, MSG_SIZE, 0);

    msgctl(queue_id, IPC_RMID, NULL);
    exit(EXIT_SUCCESS);
}

void print_message(){
    msgbuf* msg = malloc(sizeof(msgbuf));
    
    while(msgrcv(client_id, msg, MSG_SIZE, 0, MSG_NOERROR ) >= 0){
        if(msg->type != STOP){
            printf("From: %d\nMessage: %s\nAt: %s\n", msg->sender_id, msg->text, ctime(&( msg->time )));
        }
        else{
            stop_handler();
        }
    }
}

int main(int arg, char** args){
    srand(time(NULL));

    key_t server_key = ftok(HOME, SERVER_ID);
    key_t client_key = ftok(HOME, rand()%256);

    server_id = msgget(server_key, 0);
    queue_id = msgget(client_key, IPC_CREAT | 0666 );
    
    if (server_id == -1 || queue_id == -1){
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    signal(SIGINT, stop_handler);

    init();
    
    line = calloc(LINE_LEN, sizeof(char));
    
    size_t len = 0;

    while(TRUE){

        getline(&line, &len, stdin);        
        char* context = calloc(sizeof(len)+1,sizeof(char));
        strcpy(context, line);

        char* command = strtok(line, " ");
        
        if(!strcmp(context, "LIST\n")){
            list_handler();
        }
        else if(!strcmp(context, "STOP\n")){
            free(line);
            free(context);
            stop_handler();
        }
        else if(!strcmp(command, "2ALL")){
            to_all_handler(context+strlen(command)+1);
        }

        else if(!strcmp(command, "2ONE")){
            char* receiver_id = strtok(NULL," ");
            int id;
            if( (id = atoi(receiver_id)) == 0)
                fprintf(stderr, "Invalid receiver id!\n");
            else
                to_one_handler(id, context+strlen(command)+strlen(receiver_id)+2);
        }
        else{ fprintf(stderr, "Unrecognized command! Try again.\n");}
        // free(context);

        print_message();
    }
    return 0;
}