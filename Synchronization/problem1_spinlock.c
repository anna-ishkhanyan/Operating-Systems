#include <pthread.h>
#include <stdio.h>

// Shared counter
long long counter = 0;

// Spinlock for synchronization
pthread_spinlock_t lock;

void *func(void *arg)
{
    long long i;
    for (i = 0; i < 1000000; i++) {
        pthread_spin_lock(&lock); // Acquire the lock
        counter++;
        pthread_spin_unlock(&lock); // Release the lock
    }
    return NULL;
}

int main()
{
    pthread_t t[4];

    pthread_spin_init(&lock, PTHREAD_PROCESS_PRIVATE); // initializing the spinlock

    for (int i = 0; i < 4; i++)
        pthread_create(&t[i], NULL, func, NULL);

    for (int i = 0; i < 4; i++)
        pthread_join(t[i], NULL);

    printf("Expected value: %d\n", 4 * 1000000);
    printf("Actual value: %lld\n", counter);

    pthread_spin_destroy(&lock); // destroying the spinlock
    return 0;
}
