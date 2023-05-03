#define MAX_BARBERS 10
#define MAX_CHAIRS 6
#define MAX_QUEUE 3

#define SIMULATION 0
#define BARBER 1
#define CLIENT 2

#define SEM_SIMULATION "/tmp/simulation_sem"
#define SEM_BARBERS "/tmp/barber_sem"
#define SEM_CLIENTS "/tmp/client_sem"

#define SHM_SIMULATION "/tmp/simulatin_shm"
#define SHM_CLIENTS "/tmp/client_shm"


typedef struct{
    int currently_in_queue;
    int free_barbers;

    int queue[MAX_QUEUE];
    int barber[MAX_BARBERS];
    int chairs[MAX_CHAIRS];

} barber_shop;

#define SIZE sizeof(barber_shop)


int get_semaphore(int);
int get_shared_memory(int);