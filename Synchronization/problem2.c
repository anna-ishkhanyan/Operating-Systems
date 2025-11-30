#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

long long balance = 0;

pthread_mutex_t mutex;
pthread_spinlock_t spin;

int if_mutex = 1;  // 1 is mutex, 0 is spin
int if_shortcs = 1; // 1 is short cs, 0 is long

void* deposit(void* arg) { // deposit thread
    for (int i = 0; i < 10000; i++) {

        if (if_mutex) // lock according to the argument if it is a mutex or spinlock
            pthread_mutex_lock(&mutex);
        else
            pthread_spin_lock(&spin);

        balance++; // incrementing balance

        if (!if_shortcs) // if long cs then sleep
            usleep(100);

        if (if_mutex) // unlocking
            pthread_mutex_unlock(&mutex);
        else
            pthread_spin_unlock(&spin);
    }
    return NULL;
}

void* withdraw(void* arg) { // withdraw thread
    for (int i = 0; i < 10000; i++) {

        if (if_mutex) // lock
            pthread_mutex_lock(&mutex);
        else
            pthread_spin_lock(&spin);

        balance--; // decrementing balance

        if (!if_shortcs) // if long cs then sleep
            usleep(100);

        if (if_mutex) // unlocking
            pthread_mutex_unlock(&mutex);
        else
            pthread_spin_unlock(&spin);
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 3) { // checking the number of arguments
        printf("Usage: ./{program name} {mutex or spin} {short or long}\n");
        return 1;
    }

    if (strcmp(argv[1], "mutex") == 0) // checking the lock type
        if_mutex = 1;
    else if (strcmp(argv[1], "spin") == 0)
        if_mutex = 0;
    else {
        printf("Please specify mutex or spin as arg[1]\n");
        return 1;
    }

    if (strcmp(argv[2], "short") == 0) //  choosing cs type
        if_shortcs = 1;   // short
    else if (strcmp(argv[2], "long") == 0)
        if_shortcs = 0;   // long
    else {
        printf("Please specify short or long as arg[2]\n");
        return 1;
    }

    pthread_t deposit_threads[4], withdraw_threads[4];

    pthread_mutex_init(&mutex, NULL);     // init locks
    pthread_spin_init(&spin, 0);

    for (int i = 0; i < 4; i++) // creating threads
        pthread_create(&deposit_threads[i], NULL, deposit, NULL);

    for (int i = 0; i < 4; i++)
        pthread_create(&withdraw_threads[i], NULL, withdraw, NULL);

    for (int i = 0; i < 4; i++) // joining threads
        pthread_join(deposit_threads[i], NULL);

    for (int i = 0; i < 4; i++)
        pthread_join(withdraw_threads[i], NULL);

    printf("Final balance: %lld\n", balance); // the final balance as output

    pthread_mutex_destroy(&mutex);  // destroying the locks
    pthread_spin_destroy(&spin);

    return 0;
}

// Acknowledgment: used some online sources specifically to find the functions for string operations(strcmp)
