#define _GNU_SOURCE 

#include "grid.h"
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <pthread.h>
#include <signal.h>
#include <math.h>

const int grid_width = 20;
const int grid_height = 30;
static pthread_t* pthreads;


char *create_grid()
{
    return malloc(sizeof(char) * grid_width * grid_height);
}

void destroy_grid(char *grid)
{
    free(grid);
}

void draw_grid(char *grid)
{
    for (int i = 0; i < grid_height; ++i)
    {
        // Two characters for more uniform spaces (vertical vs horizontal)
        for (int j = 0; j < grid_width; ++j)
        {
            if (grid[i * grid_width + j])
            {
                mvprintw(i, j * 2, "■");
                mvprintw(i, j * 2 + 1, " ");
            }
            else
            {
                mvprintw(i, j * 2, " ");
                mvprintw(i, j * 2 + 1, " ");
            }
        }
    }

    refresh();
}

void init_grid(char *grid)
{
    for (int i = 0; i < grid_width * grid_height; ++i)
        grid[i] = rand() % 2 == 0;
}

bool is_alive(int row, int col, char *grid)
{

    int count = 0;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
            {
                continue;
            }
            int r = row + i;
            int c = col + j;
            if (r < 0 || r >= grid_height || c < 0 || c >= grid_width)
            {
                continue;
            }
            if (grid[grid_width * r + c])
            {
                count++;
            }
        }
    }

    if (grid[row * grid_width + col])
    {
        if (count == 2 || count == 3)
            return true;
        else
            return false;
    }
    else
    {
        if (count == 3)
            return true;
        else
            return false;
    }
}

void update_grid(char *src, char *dst)
{
    for (int i = 0; i < grid_height; ++i)
    {
        for (int j = 0; j < grid_width; ++j)
        {
            dst[i * grid_width + j] = is_alive(i, j, src);
        }
    }
}

// void signal_handler(int signo) {}
void ignore_handler(int signo, siginfo_t* info, void* context) {}


void* update_block(void* arguments){

    thread_argument* arg = (thread_argument*) arguments;
    char* src = arg->src;
    char* dst = arg->dst;
    int i = arg->i;
    int j = arg->j;

    while(1){

        pause();
        
        dst[i * grid_width + j] = is_alive(i, j, src);
        
        char* tmp;
        tmp = src;
        src = dst;
        dst = tmp;
    }
}

void init_threads(char* src, char* dst){

    pthreads = malloc(sizeof(pthread_t)* grid_height*grid_width);

    struct sigaction action;
    sigemptyset(&action.sa_mask);
    action.sa_sigaction = ignore_handler;
    sigaction(SIGUSR1, &action, NULL);

    for(int index=0; index<grid_height*grid_width; index++){
        thread_argument* argument = malloc(sizeof(thread_argument));
        argument->src = src;
        argument->dst = dst;
        argument->i = floor(index/grid_width);
        argument->j = index%grid_width;

        if((pthread_create(pthreads+index, NULL, update_block, (void*)argument)) != 0){
            fprintf(stderr, "pthread_create error!\n");
        }
    }
}

void update_threads(){
    for(int index=0; index<grid_height*grid_width; index++){
        pthread_kill(pthreads[index], SIGUSR1);
    }
}