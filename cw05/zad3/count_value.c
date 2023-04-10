#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

#define PATH "/tmp/queue"

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
    double a = atof(args[1]);
    double b = atof(args[2]);
    double dx = atof(args[3]);

    double result = process_value(a,b,dx);

    char* buffer = calloc(PIPE_BUF, sizeof(char));

    size_t len;
    
    if( (len = snprintf(buffer, PIPE_BUF , "%lf\n", result)) < 0 ){
        fprintf(stderr, "Problem with converting float to char!\n");
        return 1;
    }

    int fifo = open(PATH, O_WRONLY);
    while( write(fifo, buffer, len) <= 0 ) {}
    
    close(fifo);

    return 0;
}