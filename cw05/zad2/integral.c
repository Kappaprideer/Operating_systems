#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <aio.h>
#include <sys/wait.h>
#include <sys/times.h>

#define BUFFER_SIZE 255

double rectangle_value(double x, double dx){
    return (4/( (x*x) + 1 ) )*dx;
}

double process_value(double a, double b, double dx){
    double sum = 0;
    for(double x = a+dx; x<=b; x+=dx){
        sum += rectangle_value(x,dx);
    }
    return sum;
}

int main(int arg, char** args){
    if(arg!=3){
        fprintf(stderr, "Invalid number of arguments!\n");
        return EXIT_FAILURE;    
    }

    double width = atof(args[1]);
    int count = atoi(args[2]);
    double result = 0;

    struct timespec timespec_start, timespec_end;
    clock_gettime(CLOCK_REALTIME, &timespec_start);
    
    for(int process_count = 1; process_count <= count ; process_count++){
        int fd[2];
        double value;
        pipe(fd);

        pid_t pid = fork();

        if(pid == 0 ){ // child
            close(fd[0]);
            value = process_value((process_count-1)*(1.0/count), (process_count)*(1.0/count), width);

            char buffer[BUFFER_SIZE];
            if(snprintf(buffer, sizeof(buffer), "%f", value) < 0 ){
                fprintf(stderr, "Problem with converting float to char!\n");
                exit(EXIT_FAILURE);
            }

            if( write(fd[1], buffer, sizeof(buffer)) == -1){
                fprintf(stderr, "Problem with writing to pipe!\n");
                exit(EXIT_FAILURE);
            }
            exit(EXIT_SUCCESS);
        }

        else{
            close(fd[1]);
            char buffer[BUFFER_SIZE];
            read(fd[0], buffer, sizeof(buffer));

            if(wait(NULL) == -1){
                fprintf(stderr, "Problem with wait function!\n");
                return EXIT_FAILURE;
            }
            result+=atof(buffer);
        }
    }

    clock_gettime(CLOCK_REALTIME, &timespec_end);
    double sec = (timespec_end.tv_sec - timespec_start.tv_sec); 
    double nan = (timespec_end.tv_nsec - timespec_start.tv_nsec);
    nan = nan < 0 ? (nan+1000000000)/1000000000 : nan/1000000000;

    printf("Width: %s N: %d\n", args[1], count);
    printf("Integral value: %f\n", result);
    printf("Time: %fs\n\n", sec + nan);

    return 0;
}