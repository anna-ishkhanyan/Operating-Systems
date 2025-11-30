#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t printers; // counting semaphore representing available printers
pthread_mutex_t mutex; // mutex for protecitng shared variable 
int counter = 0;  // currently printing thread count

void *print_job(void *arg)
{
    int id = *(int *)arg;

    sem_wait(&printers); // waiting until a printer is available

    pthread_mutex_lock(&mutex);
    counter++; // incrementing the count of printing threads
    printf("Thread %d printing counter %d\n", id, counter);
    pthread_mutex_unlock(&mutex);

    usleep(300000); // printing time

    pthread_mutex_lock(&mutex);
    counter--; // decrementing the count of printing threads
    printf("Thread %d finished.\n", id);
    pthread_mutex_unlock(&mutex);

    sem_post(&printers); // done

    return NULL;
}

int main()
{
    pthread_t threads[10]; // N = 10 as required
    int id[10]; 

    sem_init(&printers, 0, 3); //  K is 3
    pthread_mutex_init(&mutex, NULL); // initializing mutex

    for (int i = 0; i < 10; i++) { // creating the threads
        id[i] = i;
        pthread_create(&threads[i], NULL, print_job, &id[i]);
    }

    for (int i = 0; i < 10; i++) // waiting for the threads to finish
        pthread_join(threads[i], NULL);

    pthread_mutex_destroy(&mutex); // destroying mutex and semaphore
    sem_destroy(&printers);

    return 0;
}
