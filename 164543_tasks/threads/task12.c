/* REQUIRED HEADER FILES */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* MACRO DEFINITIONS */
#define NUM_THREADS 10
#define LOOP_COUNT 1000

static int glob = 0; 
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; /* Mutex for locking */

/* incrementCounter: Thread function */
static void *incrementCounter(void *arg) {
    for (int j = 0; j < LOOP_COUNT; j++) {
        pthread_mutex_lock(&lock); /* Acquire lock */
        glob++; /* Increment the counter */
        pthread_mutex_unlock(&lock); /* Release lock */
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int s;

    /* Create threads */
    for (int i = 0; i < NUM_THREADS; i++) {
        s = pthread_create(&threads[i], NULL, incrementCounter, NULL);
        if (s != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    /* Wait for threads to finish */
    for (int i = 0; i < NUM_THREADS; i++) {
        s = pthread_join(threads[i], NULL);
        if (s != 0) {
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }

    printf("Final value of glob with locking: %d (expected: %d)\n", glob, NUM_THREADS * LOOP_COUNT);

    
    return 0;
}

