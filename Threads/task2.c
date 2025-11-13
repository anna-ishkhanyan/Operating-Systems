#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define ARRAY_SIZE 100

int array[ARRAY_SIZE];
long partial_sums[2]; // array to store partial sums

void* sum_array(void* arg) {
    int thread_id = *((int*) arg);
   
    long sum = 0;
    for (int i = thread_id * (ARRAY_SIZE / 2); i < (thread_id + 1) * (ARRAY_SIZE / 2); i++) {
        sum += array[i];
    }

    partial_sums[thread_id] = sum;
    printf("partial sum from thread %d = %ld\n", thread_id, sum);

    return NULL;
}

int main() {
    // initialize array
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = i + 1;
    }

    pthread_t threads[2];
    int thread_ids[2] = {0, 1};

    // create two threads
    for (int i = 0; i < 2; i++) {
        pthread_create(&threads[i], NULL, sum_array, (void*)&thread_ids[i]);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
// used the logic from aua-os github
