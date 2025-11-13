#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* function(void* arg) {
    int id = *((int*)arg);
    for(int i = 1; i < 4; i++) {
        printf("This is thread %d.\n", id);
    }
    printf("Thread ID: %p\n", (void*)pthread_self());
    return NULL;
}

int main() {
    pthread_t threads[3];
    int thread_ids[3] = {1, 2, 3};

    for (int i = 0; i < 3; i++) {
    pthread_create(&threads[i], NULL, function, &thread_ids[i]);
    }
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("Done\n");
    return 0;
}
