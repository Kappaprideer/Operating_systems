#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

/*
 wyslac sygnal SIGUSR1 do samego siebie
 signal ma obsluzyc sygnał i wyprintować ,,ja cie ale sygnal"
*/
void handle_sig(int signum){
    printf("Ja cie ale sygnal\n\n");
}
int main(){
    while(1){
        sleep(1);
        printf("DZIALA CALY CZAS\n");
        signal(SIGUSR1, handle_sig);
        raise(SIGUSR1);
    }
    return 0;
}
