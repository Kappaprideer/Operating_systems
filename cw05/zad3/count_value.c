#include <stdlib.h>
#include <stdio.h>


#define BUFFER_SIZE 512
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


    char buffer[BUFFER_SIZE];

    size_t len;
    
    if((len = snprintf(buffer, BUFFER_SIZE , "%lf\n", result)) < 0 ){
        fprintf(stderr, "Problem with converting float to char!\n");
        return 1;
    }

    FILE* fifo = fopen(PATH , "w");
    while( fwrite(buffer, sizeof(char), len, fifo) <= 0 ) {}
    fclose(fifo);

    printf("BUFFER: %s\n", buffer);

    return 0;
}