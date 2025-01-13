/* Write a program where the main default thread spawns N threads. Thread i should print 
the message “I am thread i” to screen and exit. The main thread should wait for all N 
threads to finish, then print the message “I am the main thread”, and exit. */
/* REQUIRED HEADER FILES */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *threadFunc(void *arg) {
    int thread_id = *((int *)arg); // Retrieve the thread ID
    printf("I am thread %d\n", thread_id);
    free(arg); // Free dynamically allocated memory
    return NULL;
}

int main(int argc, char *argv[]) {
    int iNum ,i ;
    /* Validate input for number of threads */
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number_of_threads>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

  
    iNum = atoi(argv[1]);
    pthread_t threads[iNum]; /* Array to store thread IDs */

    
    for (i = 0; i < iNum; i++) {
        int *thread_id = malloc(sizeof(int)); 
        if (thread_id == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        *thread_id = i + 1; /* Assign a unique ID to each thread */

        if (pthread_create(&threads[i], NULL, threadFunc, thread_id) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    /* Wait for all threads to finish */
    for ( i = 0; i < iNum; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }

    /* Print main thread message */
    printf("I am the main thread..exit\n");

    return 0;
}

