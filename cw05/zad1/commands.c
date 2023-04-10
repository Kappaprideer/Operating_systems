#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 1024


// z uwagi na problemy z instalacją programu „mail" wykorzystałem komendy:
// - zamiast sortowania list maili: wyświetla sl lub fortune w zależności od argumentu (train lub quote)
// - zamiast wysłania maila uruchamia polecenie figet dla 3 wyrazow wykorzystując odpowiednio popen

void run_figlet(char* arg1, char* arg2, char* arg3) {

    char command[BUFFER_SIZE];
    
    sprintf(command,"%s %s %s", arg1, arg2, arg3);
    
    FILE* pipe = popen("figlet", "w");
    fputs(command,pipe);    
    pclose(pipe);
}


int main(int arg, char** args ) {
    if(arg == 2){
        char command[BUFFER_SIZE];
        if (strcmp(args[1], "train") == 0) {
            sprintf(command, "sl");

        } else if (strcmp(args[1], "quote") == 0) {
            sprintf(command, "fortune");

        } else {
            fprintf(stderr, "Wrong argument!\n");
            exit(EXIT_FAILURE);
        }

        FILE* pipe = popen(command, "r");

        char buffer[BUFFER_SIZE];

        while (fgets(buffer, BUFFER_SIZE, pipe) != NULL) {
            printf("%s", buffer);
        }
        pclose(pipe);
    }

    else if (arg == 4) {
        run_figlet(args[1], args[2], args[3]);
    }
    else{
        fprintf(stderr, "Invalid number of arguments!\n");
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}