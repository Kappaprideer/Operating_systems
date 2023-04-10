#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>

#define PATH "/tmp/queue"

int main(int arg, char** args){
    if(arg!=3){
        fprintf(stderr, "Invalid number of arguments!\n");
        return EXIT_FAILURE;    
    }

    int count = atoi(args[2]);

    struct timespec timespec_start, timespec_end;
    clock_gettime(CLOCK_REALTIME, &timespec_start);
    
    mkfifo(PATH, 0666 );

    for(int process_count = 1; process_count <= count ; process_count++){
        if(fork() == 0 ){
            char a[PIPE_BUF];
            char b[PIPE_BUF];
            
            snprintf(a,  PIPE_BUF, "%f", (process_count-1)*(1.0/count));
            snprintf(b,  PIPE_BUF, "%f", (process_count)*(1.0/count));

            execl("./count_value", "count_value", a, b, args[1], NULL);
        }
    }

    double result = 0;
    int read_count = 0;
    char* buffer = calloc(PIPE_BUF, sizeof(char));
    
    int fifo = open(PATH, O_RDONLY);

    while(read_count < count){
        
        size_t len = read(fifo, buffer, PIPE_BUF);
        
        if(len>0){
            char *token;
            token = strtok(buffer, "\n");
                
            while (token != NULL){
                result+=atof(token);
                token = strtok(NULL,"\n");
                read_count++;
            }

            free(buffer);
            buffer = calloc(PIPE_BUF, sizeof(char));
        }
    }

    close(fifo);
    free(buffer);
    remove(PATH);

    clock_gettime(CLOCK_REALTIME, &timespec_end);
    double sec = (double)(timespec_end.tv_sec - timespec_start.tv_sec);
    double nan = (double)(timespec_end.tv_nsec - timespec_start.tv_nsec);
    nan = nan < 0 ? (nan+1000000000)/1000000000 : nan/1000000000;

    printf("Width: %s N: %d\n", args[1], count);
    printf("Integral value: %f\n", result);
    printf("Time: %fs\n\n", sec + nan);

    return 0;
}