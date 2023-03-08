#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>
#include <unistd.h>
#include "../zad1/library.h"
#include "dllmana.h"

const int QUERY_LENGTH = 100;
const int MAX_WORDS = 3;

struct timespec timespec_start, timespec_end;
struct tms tms_start, tms_end;

void end_time_measure(){
    clock_gettime(CLOCK_REALTIME, &timespec_end);
    times(&tms_end);
    printf("REAL TIME: %ld nanosec\n", timespec_end.tv_nsec - timespec_start.tv_nsec );
    printf("USER TIME: %ld tics \n", tms_end.tms_cutime - tms_start.tms_cutime );
    printf("SYST TIME: %ld tics \n", tms_end.tms_cstime - tms_start.tms_cstime );
}


void error(int numberGivenWords, int numberExpectedWords){
    fprintf(stderr,"Wrong number of arguments!\nYou gave %d instead of %d expected.\n",numberGivenWords,numberExpectedWords);
}

int main(){
    int query_number = 0;
    int exit_program = 0;
    char **words = (char**) malloc(sizeof(char*)*MAX_WORDS);
    char *word;
    char *query = (char*) malloc(sizeof(char)*QUERY_LENGTH);

    chars_pointer* memory_blocks = NULL;

    while( query_number<INT_MAX && !exit_program ){
        printf("In [%d]: ", query_number++);
        fgets(query,QUERY_LENGTH,stdin);
        fflush(NULL);
        word = strtok(query, " ");

        int word_counter = 0;
        while( word != NULL ) {
            if (strcmp(word,"") != 0 && strcmp(word,"\n") != 0 && word_counter < MAX_WORDS ){
                words[word_counter++] = word;
            }
            word = strtok(NULL, " ");
        }

//      MIERZENIE CZASU
        clock_gettime(CLOCK_REALTIME, &timespec_start);
        times(&tms_start);

        if( strcmp(words[0],"init\n") == 0 || strcmp(words[0],"init") == 0){
            if( word_counter != 2){
                error(word_counter,2);
            }
            else{
                int tabSize = atoi(words[1]);
                memory_blocks = init(tabSize);
                end_time_measure();
                sleep(1);
            }
        }

        else if( strcmp(words[0],"count\n") == 0 || strcmp(words[0],"count") == 0){
            if( word_counter != 2){
                error(word_counter,2);
            }
            char* file_name = (char*) calloc(sizeof(char), strlen(words[1]));
            memcpy(file_name,words[1],strlen(words[1])-1);

            count(memory_blocks,file_name);
            free(file_name);
            end_time_measure();
            sleep(1);
        }

        else if( strcmp(words[0],"show\n") == 0 || strcmp(words[0],"show") == 0){
            if( word_counter != 2) {
                error(word_counter, 2);
            }
            int memory_block_index=atoi(words[1]);
            printf("%s\n", show(memory_blocks, memory_block_index));
            end_time_measure();
            sleep(1);
        }
        else if( strcmp(words[0],"delete\n") == 0 || strcmp(words[0],"delete") == 0){
            if( word_counter != 2){
                error(word_counter,3);
            }
            int memory_block_index=atoi(words[1]);
            delete(memory_blocks, memory_block_index);
            end_time_measure();
            sleep(1);
        }

        else if( strcmp(words[0], "destroy\n") == 0 || strcmp(words[0], "destroy") == 0){
            destroy(memory_blocks);
            end_time_measure();
            sleep(1);
        }

        else if( strcmp(words[0], "exit\n")==0 || strcmp(words[0], "exit") ==0 ){
            exit_program=1;
        }

        else{
            printf("Command not found!\n");
            end_time_measure();
            sleep(1);
        }
    }
    free(words);
    free(query);
}