#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>



const int QUERY_LENGTH = 100;
const int MAX_WORDS = 3;

void error(int numberGivenWords, int numberExpectedWords){
    fprintf(stderr,"Wrong number of arguments!\nYou gave %d instead of %d expected.\n",numberGivenWords,numberExpectedWords);
}


int main(){
    int query_number = 0;
    int exit_program = 0;
    char **words = (char**) malloc(sizeof(char*)*MAX_WORDS);
    char *word;
    char *query = (char*) malloc(sizeof(char)*QUERY_LENGTH);
    while( query_number < INT_MAX && !exit_program ){
        printf("In [%d]: ", query_number++);
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
            }

        }
        else if( strcmp(words[0],"count\n") == 0 || strcmp(words[0],"count") == 0){
            if( word_counter != 2){
                error(word_counter,2);
            }
            printf("count size: ");
        }
        else if( strcmp(words[0],"show\n") == 0 || strcmp(words[0],"show") == 0){
            if( word_counter != 2){
                error(word_counter,2);
            }
            printf("show size: ");
        }
        else if( strcmp(words[0],"delete\n") == 0 || strcmp(words[0],"delete") == 0){
            if( word_counter != 3){
                error(word_counter,3);
            }
            printf("delete size: ");
        }
        else{
            printf("Not found that commend!\n");
        }

    }
    free(words);
    free(query);
}