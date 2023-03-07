#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../zad1/library.h"
//#include <dlfcn.h>

//int main() {
//    void *handle = dlopen("libmy_library.so", RTLD_LAZY);
//    if(!handle){/*error*/}
//
//    void (*lib_fun)();
//    lib_fun = (void (*)())dlsym(handle,"my_library_function");
//
//    if(dlerror() != NULL){/*error*/}
//
//    (*lib_fun)();
//
//    dlclose(handle);
//}


const int QUERY_LENGTH = 100;
const int MAX_WORDS = 3;

void error(int numberGivenWords, int numberExpectedWords){
    fprintf(stderr,"Wrong number of arguments!\nYou gave %d instead of %d expected.\n",numberGivenWords,numberExpectedWords);
}

void execute_command(char* command, int index){

}



int main(){
    int query_number = 0;
    int exit_program = 0;
    char **words = (char**) malloc(sizeof(char*)*MAX_WORDS);
    char *word;
    char *query = (char*) malloc(sizeof(char)*QUERY_LENGTH);

    chars_pointer* memory_blocks;

    while( query_number<INT_MAX && !exit_program ){

        printf("In [%d]: ", query_number++);
        fflush(NULL);
        fgets(query,QUERY_LENGTH,stdin);
        word = strtok(query, " ");

        int word_counter = 0;
        while( word != NULL ) {
            if (strcmp(word,"") != 0 && strcmp(word,"\n") != 0 && word_counter < MAX_WORDS ){
                words[word_counter++] = word;
            }
            word = strtok(NULL, " ");
        }

        if( strcmp(words[0],"init\n") == 0 || strcmp(words[0],"init") == 0){
            if( word_counter != 2){
                error(word_counter,2);
            }
            else{
                int tabSize = atoi(words[1]);
                memory_blocks = init(tabSize);
            }
        }

        else if( strcmp(words[0],"count\n") == 0 || strcmp(words[0],"count") == 0){
            if( word_counter != 2){
                error(word_counter,2);
            }
            count(memory_blocks,words[1]);
        }

        else if( strcmp(words[0],"show\n") == 0 || strcmp(words[0],"show") == 0){
            if( word_counter != 2) {
                error(word_counter, 2);
            }
            int memory_block_index=atoi(words[1]);
            printf("Index number: %d\n", memory_block_index);
            printf("Should show: %s \n", show(memory_blocks, memory_block_index));
        }

        else if( strcmp(words[0],"delete\n") == 0 || strcmp(words[0],"delete") == 0){
            if( word_counter != 3){
                error(word_counter,3);
            }
            int memory_block_index=atoi(words[1]);
            printf("\nIndex number: %d\n", memory_block_index);
            delete(memory_blocks, memory_block_index);
        }

        else if( strcmp(words[0], "exit\n")==0 || strcmp(words[0], "exit") ==0 ){
            exit_program=1;
        }
        else{
            printf("Command not found!\n");
        }

    }
    free(words);
    free(query);
}