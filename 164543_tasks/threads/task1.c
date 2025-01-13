/* Write a program that has a counter as a global variable. Spawn 10 threads in the program, 
and let each thread increment the counter 1000 times in a loop. Print the final value of the 
counter after all the threads finish—the expected value of the counter is 10000. Run this 
program first without using locking across threads, and observe the incorrect updation of 
the counter due to race conditions (the final value will be slightly less than 10000). Next, 
use locks when accessing the shared counter and verify that the counter is now updated 
correctly. */
/* REQUIRED HEADER FILES */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
/* MACRO DEFINITIONS */
#define NUM_THREADS 10
#define LOOP_COUNT 1000

static int glob = 0; /* Shared global counter */

/* Thread function */
static void *incrementCounter(void *arg) {
    for (int j = 0; j < LOOP_COUNT; j++) {
        glob++; /* Increment the counter */
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

    printf("Final value of glob without locking: %d (expected: %d)\n", glob, NUM_THREADS * LOOP_COUNT);
    return 0;
}

