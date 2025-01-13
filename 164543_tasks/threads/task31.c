/* REQUIRED HEADER FILES */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>


pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int current_thread = 1; /* Keeps track of the thread expected to print */

void *threadFunc(void *arg) {
    int thread_id = *((int *)arg); 
    free(arg); 

    
    int sleep_time = (rand() % 10) + 1; 
    sleep(sleep_time);

    /* Synchronize the order of thread execution */
    pthread_mutex_lock(&lock);
    while (thread_id != current_thread) {
        pthread_cond_wait(&cond, &lock); /* Wait until it's this thread's turn */
    }

    // Print the message for the current thread
    printf("I am thread %d\n", thread_id);

    /* Update the expected thread ID and signal other threads */
    current_thread++;
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main(int argc, char *argv[]) {
    int N;

    /* Validate input for the number of threads */
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number_of_threads>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    N = atoi(argv[1]);
    if (N <= 0) {
        fprintf(stderr, "Number of threads must be a positive integer.\n");
        exit(EXIT_FAILURE);
    }

    pthread_t threads[N];

    /* Seed the random number generator */
    srand(time(NULL));

    // Create N threads
    for (int i = 0; i < N; i++) {
        int *thread_id = malloc(sizeof(int)); // Allocate memory for thread ID
        if (thread_id == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        *thread_id = i + 1; // Assign a unique ID to each thread

        if (pthread_create(&threads[i], NULL, threadFunc, thread_id) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    /* Wait for all threads to finish */
    for (int i = 0; i < N; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }


    return 0;
}

