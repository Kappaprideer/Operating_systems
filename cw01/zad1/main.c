#include <stdio.h>
#include "library.h"


int main() {
    chars_pointer* mem = init(20);
    count_file(mem, "/home/endrew/Github/Operating_systems/cw01/zad1/files/nowe.txt" );
    printf("%s" "%c", show_index(mem, 0), '\n');
    count_file(mem, "/home/endrew/Github/Operating_systems/cw01/zad1/files/dwa.txt" );
    printf("%s" "%c", show_index(mem, 1), '\n');
    count_file(mem, "/home/endrew/Github/Operating_systems/cw01/zad1/files/trzy.txt" );
    printf("%s" "%c", show_index(mem, 2), '\n');
    count_file(mem, "/home/endrew/Github/Operating_systems/cw01/zad1/files/cztery.txt" );
    printf("%s" "%c", show_index(mem, 3), '\n');
    delete_index(mem,4);
    delete_index(mem,1);
    printf("%s" "%c", show_index(mem,1), '\n');
    count_file(mem, "/home/endrew/Github/Operating_systems/cw01/zad1/files/nowe.txt" );
    printf("%s" "%c", show_index(mem,1), '\n');
    destroy(mem);

    return 0;
}