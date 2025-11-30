#include <stdio.h>
#include <pthread.h>

// Shared variable
long long counter = 0;

// Mutex for synchronization
pthread_mutex_t mutex;

// Thread function to increment counter
void *func(void *arg)
{
    for (long long i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&mutex); // Acquire the mutex
        counter++; 
        pthread_mutex_unlock(&mutex); // Release the mutex
    }
    return NULL;
}

int main()
{
    pthread_t t[4];

    pthread_mutex_init(&mutex, NULL); // Initialize the mutex

    for (int i = 0; i < 4; i++)
        // Create threads
        pthread_create(&t[i], NULL, func, NULL);

    for (int i = 0; i < 4; i++)
        pthread_join(t[i], NULL);

    printf("Expected value: %d\n", 4 * 1000000);
    printf("Actual value: %lld\n", counter);

    pthread_mutex_destroy(&mutex); // destroying mutex
    
    return 0;
}
