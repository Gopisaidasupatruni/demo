#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_KEY 5678
#define SHM_SIZE 1024

int main() {
    int shm_id;
    char *shared_mem;

    /* Create shared memory */
    shm_id = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666);
    if (shm_id < 0) {
        perror("shmget");
        exit(1);
    }

    /* Attach to shared memory */
    shared_mem = shmat(shm_id, NULL, 0);
    if (shared_mem == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    /* Write data */
    printf("Enter data to write to shared memory: ");
    fgets(shared_mem, SHM_SIZE, stdin);

    printf("Data written to shared memory.\n");
    return 0;
}

