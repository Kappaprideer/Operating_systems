#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/msg.h>
#include <signal.h>


int main(int arg, char** args){

    key_t key = ftok("/tmp/serv", 'a');

    int mymsgq = msgget(key, IPC_CREAT | 0666 );
    if (mymsgq == -1){
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // zad 2
    struct msqid_ds stat;
    // ret = msgctl(msqid, )    




    return 0;
}




