#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 5

int numbers[ARRAY_SIZE];

void* square(void* arg) {
    int num = *((int*)arg);
    printf("%d^2 is %d\n", num, num * num);
    return NULL;
}

int main() {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        numbers[i] = i + 1;
    }

    pthread_t threads[ARRAY_SIZE];

    // Create one thread for each number
    for (int i = 0; i < ARRAY_SIZE; i++) {
        pthread_create(&threads[i], NULL, square, &numbers[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < ARRAY_SIZE; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Done.\n");
    return 0;
}
