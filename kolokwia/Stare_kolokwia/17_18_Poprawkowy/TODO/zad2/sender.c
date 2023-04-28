#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define PIPE "./squareFIFO"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Not a suitable number of program parameters\n");
        return (1);
    }

    // utworz potok nazwany pod sciezka reprezentowana przez PIPE
    // zakladajac ze parametrem wywolania programu jest liczba calkowita
    // zapisz te wartosc jako int do potoku i posprzataj

    /* FROM HERE */
    mkfifo(PIPE, 0666);
    int fd = open(PIPE, O_WRONLY);
    int value = atoi(argv[1]);
    write(fd, &value, sizeof(int));
    close(fd);
    /* TILL HERE */

    return 0;
}
