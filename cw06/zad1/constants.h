// #ifndef CONSTANTS_H
// #define CONSTANTS_H

#include <stdio.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 1
#define FALSE 0

#define HOME "/tmp/queue"
#define SERVER_ID 5
#define MSG_LEN 512
#define MAX_CLIENTS 10

#define INIT 0

#define LIST 1
#define TO_ALL 2
#define TO_ONE 3
#define STOP 4


typedef struct msgbuf {
  long type;         /* typ komunikatu   */
  time_t time;
  int sender_id;
  int receiver_id;
  char text[MSG_LEN];      /* tresc komunikatu */
} msgbuf;
