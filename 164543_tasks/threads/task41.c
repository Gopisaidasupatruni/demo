#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int current_thread = 1; 
int N;                 

void *threadFunc(void *arg) {
    int thread_id = *((int *)arg); /* Get the thread ID */
    free(arg); /* Free the allocated memory for thread ID */

    while (1) { /* Continuous loop */
        pthread_mutex_lock(&lock);

        /* Wait until it's this thread's turn */
        while (thread_id != current_thread) {
            pthread_cond_wait(&cond, &lock);
        }

        /* Print the thread's number */
        printf("%d ", thread_id);
        fflush(stdout); 
	/* Update the current thread to the next one in the sequence */
        current_thread = (current_thread % N) + 1;

        /* Signal other threads and unlock the mutex */
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&lock);

            sleep(1);
    }

    return NULL;
}

int main(int argc, char *argv[]) {
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

    /* Create N threads*/
    for (int i = 0; i < N; i++) {
        int *thread_id = malloc(sizeof(int));
        if (thread_id == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        *thread_id = i + 1; /*Assign a unique ID to each thread*/

        if (pthread_create(&threads[i], NULL, threadFunc, thread_id) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);

    return 0;
}

