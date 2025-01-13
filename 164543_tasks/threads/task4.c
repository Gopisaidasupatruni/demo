
/* REQUIRED HEADER FILES */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

void *threadFunc(void *arg) {
    int thread_id = *((int *)arg); 
    free(arg); 

    /* Generate a random sleep interval (1 to 10 seconds) */
    int sleep_time = (rand() % 10) + 1; 
    sleep(sleep_time);
 while (1) { // Continuous loop
        printf("%d ", thread_id);
        fflush(stdout); // Ensure immediate output
		sleep(1);
    }

    /* Print the thread message */
    printf("I am thread %d\n", thread_id);

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

    /* Create N threads */
    for (int i = 0; i < N; i++) {
        int *thread_id = malloc(sizeof(int)); 
        if (thread_id == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        *thread_id = i + 1; 

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

