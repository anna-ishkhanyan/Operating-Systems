#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

long long counter = 0;

void* func(void* arg) {
    for (long long i = 0; i < 1000000; i++) {
        counter++;
    }
    return NULL;
}

int main() {
    pthread_t threads[4];

    for (int i = 0; i < 4; i++)
        pthread_create(&threads[i], NULL, func, NULL);

    for (int i = 0; i < 4; i++)
        pthread_join(threads[i], NULL);

    printf("Expected value: %d\n", 4 * 1000000);
    printf("Actual value: %lld\n", counter);

    return 0;
}
