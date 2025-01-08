#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

#define SEM_KEY 1234

// Semaphore operations
void sem_lock(int sem_id) {
    struct sembuf sb = {0, -1, 0}; // P operation (decrement)
    if (semop(sem_id, &sb, 1) < 0) {
        perror("semop - lock");
        exit(1);
    }
}

void sem_unlock(int sem_id) {
    struct sembuf sb = {0, 1, 0}; // V operation (increment)
    if (semop(sem_id, &sb, 1) < 0) {
        perror("semop - unlock");
        exit(1);
    }
}

int main() {
    int sem_id;

    // Create or access a semaphore
    sem_id = semget(SEM_KEY, 1, IPC_CREAT | 0666);
    if (sem_id < 0) {
        perror("semget");
        exit(1);
    }

    // Initialize semaphore to 1 (unlocked state)
    if (semctl(sem_id, 0, SETVAL, 1) < 0) {
        perror("semctl - SETVAL");
        exit(1);
    }

    printf("Process %d waiting to enter critical section...\n", getpid());
    sem_lock(sem_id); // Lock the semaphore

    // Critical section
    printf("Process %d in critical section.\n", getpid());
    sleep(2); // Simulate work in the critical section

    printf("Process %d leaving critical section.\n", getpid());
    sem_unlock(sem_id); // Unlock the semaphore

    return 0;
}

