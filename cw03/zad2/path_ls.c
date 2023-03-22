#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int arg, char** args){
    if(arg != 2){
        fprintf(stderr, "Wrong number of arguments!\n");
        return EXIT_FAILURE;
    }

    char* program_name = malloc(sizeof(char)*(strlen(args[0])-2));
    
    strncpy(program_name, args[0]+2, strlen(args[0])-2);
    
    printf("%s ", program_name);
    
    free(program_name);

    fflush(stdout);

    execl("/bin/ls", "/bin/ls", args[1], NULL);

    return EXIT_SUCCESS;
}