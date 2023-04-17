#include <stdio.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 1
#define FALSE 0

#define HOME getenv("HOME")
#define SERVER_ID 1
#define MSG_LEN 512
#define MAX_CLIENTS 10

#define INIT 1

#define LIST 2
#define TO_ALL 3
#define TO_ONE 4
#define STOP 5


typedef struct msgbuf {
  long type;
  time_t time;
  int sender_id;
  int receiver_id;
  char text[MSG_LEN];
} msgbuf;
