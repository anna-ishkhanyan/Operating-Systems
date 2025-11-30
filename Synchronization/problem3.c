#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 8

int buffer[BUFFER_SIZE];
int in_pos = 0;
int out_pos = 0;

sem_t empty_slots;  // the number of empty slots remained
sem_t full_slots;  // the number of full slots existing
pthread_mutex_t buffer_mutex;

int P = 3;  // the number of producers
int C = 3;  // the number of consumers
int K = 10; // the number of items produced

int consumed = 0;  // track of consumed items

void* producer(void* arg) {
    for (int i = 0; i < K; i++) {

        sem_wait(&empty_slots);  // waiting for an empty slot
        pthread_mutex_lock(&buffer_mutex);

        buffer[in_pos] = 1;  // writing an item
        in_pos = (in_pos + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&buffer_mutex);
        sem_post(&full_slots); // one more full slot
    }
    return NULL;
}

void* consumer(void* arg) {
    while (1) {

        pthread_mutex_lock(&buffer_mutex);
        if (consumed >= P * K) {  // checking if all items are consumed
            pthread_mutex_unlock(&buffer_mutex);
            break;
        }
        pthread_mutex_unlock(&buffer_mutex);

        sem_wait(&full_slots); // wait for an item
        pthread_mutex_lock(&buffer_mutex);

        if (consumed < P * K) {
            int item = buffer[out_pos];  // read item
            (void)item;  // item unused
            out_pos = (out_pos + 1) % BUFFER_SIZE;
            consumed++;
        }

        pthread_mutex_unlock(&buffer_mutex);
        sem_post(&empty_slots); // free one slot
    }
    return NULL;
}

int main() {

    sem_init(&empty_slots, 0, BUFFER_SIZE); // buffer starts empty
    sem_init(&full_slots, 0, 0);  // no items at first
    pthread_mutex_init(&buffer_mutex, NULL);

    pthread_t prod_threads[P], cons_threads[C];

    for (int i = 0; i < P; i++) // creating producers
        pthread_create(&prod_threads[i], NULL, producer, NULL);

    for (int i = 0; i < C; i++) // creating consumers
        pthread_create(&cons_threads[i], NULL, consumer, NULL);

    for (int i = 0; i < P; i++) // waiting for producer
        pthread_join(prod_threads[i], NULL);

    for (int i = 0; i < C; i++) // waiting for consumer
        pthread_join(cons_threads[i], NULL);

    pthread_mutex_destroy(&buffer_mutex);// destroying mutex and semaphore
    sem_destroy(&empty_slots);
    sem_destroy(&full_slots);

    return 0;
}
