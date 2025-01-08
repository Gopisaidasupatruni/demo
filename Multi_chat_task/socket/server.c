#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>
#include <unistd.h>

#define SHM_SIZE 1024    /* Shared memory size */
#define MAX_MSG_LEN 128  /* Maximum message length */
#define SOCKET_PATH "/tmp/chat_socket"

/* Semaphore operations */
struct sembuf sem_lock = {0, -1, 0};
struct sembuf sem_unlock = {0, 1, 0};

int main() {
    int server_fd, client_fd, shm_id, sem_id;
    char *shared_mem;
    struct sockaddr_un server_addr, client_addr;
    socklen_t client_len;

    /* Creates Unix Domain Socket */
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    /* Configuring server address */
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);
    unlink(SOCKET_PATH);

    /* Bind socket */
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    /* Listen for connections */
    if (listen(server_fd, 5) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    //printf("Server listening on %s\n", SOCKET_PATH);

    /* Create shared memory */
    shm_id = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666);
    if (shm_id < 0) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    shared_mem = (char *)shmat(shm_id, NULL, 0);
    if (shared_mem == (char *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    memset(shared_mem, 0, SHM_SIZE);

    /* Create semaphore */
    sem_id = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666);
    if (sem_id < 0) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    semctl(sem_id, 0, SETVAL, 1); 

    while (1) {
        /* Accept client connection */
        client_len = sizeof(client_addr);
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
        if (client_fd < 0) {
            perror("accept");
            continue;
        }

        printf("Client connected.\n");

        // Fork to handle client
        if (fork() == 0) {
            close(server_fd);

            char buffer[MAX_MSG_LEN];
            while (1) {
                memset(buffer, 0, MAX_MSG_LEN);
                ssize_t bytes_read = read(client_fd, buffer, MAX_MSG_LEN);
                if (bytes_read <= 0) {
                    printf("Client disconnected.\n");
                    close(client_fd);
                    exit(0);
                }

                /* Synchronize access to shared memory using semaphore */
                semop(sem_id, &sem_lock, 1);

                /* Write to shared memory */
                strncat(shared_mem, buffer, SHM_SIZE - strlen(shared_mem) - 1);

                semop(sem_id, &sem_unlock, 1);

                printf("Message received: %s", buffer);
            }
        }

        close(client_fd);
    }

    /* Cleanup (on server termination) */
    shmctl(shm_id, IPC_RMID, NULL);
    semctl(sem_id, 0, IPC_RMID);
    unlink(SOCKET_PATH);

    return 0;
}

