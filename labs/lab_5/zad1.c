#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(){

    FILE* file;
    file = fopen("out.txt","w");

    int fd[2];
    pipe(fd);
    
    




    return 0;
}