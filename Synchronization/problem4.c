#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

sem_t semA; // semaphores
sem_t semB;
sem_t semC;

pthread_mutex_t print_mutex;

void *thread_A(void *arg)
{
    for (int i = 0; i < 4; i++) { // number of thread is 4

        sem_wait(&semA); // waiting until the A's turn

        pthread_mutex_lock(&print_mutex); // a mutex to protect printf
        printf("A %d\n", i);
        pthread_mutex_unlock(&print_mutex);

        sem_post(&semB); // B starts next
    }
    return NULL;
}

void *thread_B(void *arg)
{
    for (int i = 0; i < 4; i++) {

        sem_wait(&semB); // waiting until a signal from A

        pthread_mutex_lock(&print_mutex);
        printf("B %d\n", i);
        pthread_mutex_unlock(&print_mutex);

        sem_post(&semC); // C runs next
    }
    return NULL;
}

void *thread_C(void *arg)
{
    for (int i = 0; i < 4; i++) {

        sem_wait(&semC); // waiting until signal from B to start

        pthread_mutex_lock(&print_mutex);
        printf("C %d\n", i);
        pthread_mutex_unlock(&print_mutex);

        sem_post(&semA); // signal to run A 
    }
    return NULL;
}

int main()
{
    pthread_t A, B, C;

    sem_init(&semA, 0, 1); // initializing semaphores, here A starts first
    sem_init(&semB, 0, 0);
    sem_init(&semC, 0, 0);

    pthread_mutex_init(&print_mutex, NULL); // starting mutex

    pthread_create(&A, NULL, thread_A, NULL); // creating the threads
    pthread_create(&B, NULL, thread_B, NULL);
    pthread_create(&C, NULL, thread_C, NULL);

    pthread_join(A, NULL); // waiting for the threads to finish
    pthread_join(B, NULL);
    pthread_join(C, NULL);

    sem_destroy(&semA); // destroying semaphores and mutex
    sem_destroy(&semB);
    sem_destroy(&semC);
    pthread_mutex_destroy(&print_mutex);

    return 0;
}
