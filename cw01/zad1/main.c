#include <stdio.h>
//#include <"library.h">

int main() {

    char* buff;
    chars_pointer* mem = init(20);
    count_file(mem, "/home/endrew/Github/Operating_systems/cw01/zad1/nowe.txt" );
    buff = show_index(mem, 0);
    count_file(mem, "/home/endrew/Github/Operating_systems/cw01/zad1/dwa.txt" );
    buff = show_index(mem, 1);
    count_file(mem, "/home/endrew/Github/Operating_systems/cw01/zad1/trzy.txt" );
    buff = show_index(mem, 2);
    count_file(mem, "/home/endrew/Github/Operating_systems/cw01/zad1/cztery.txt" );
    buff = show_index(mem, 3);


    return 0;
}