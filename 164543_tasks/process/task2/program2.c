#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 10
#define M_MIN -999999999
#define M_MAX 999999999

/* PWork: Parent process function */
void PWork(int read_fd, int write_fd) {
    char buffer[BUFFER_SIZE];
    long M;

    printf("[Parent] Ready to proceed. PID: %d\n", getpid());

    // Start with an initial value for M
    snprintf(buffer, BUFFER_SIZE, "%d", 1); // Start the value from 1
    write(write_fd, buffer, strlen(buffer) + 1); // Write to Pipe A

    while (1) {
        // Read value from Pipe C
        read(read_fd, buffer, BUFFER_SIZE);
        M = atol(buffer); // Convert string to long integer

        // Print current value of M
        printf("[Parent] Value = %ld\n", M);

        // Check if M is out of the bounds
        if (M < M_MIN || M > M_MAX) {
            break;
        }

        // Update M
        M = 200 - 3 * M;
        snprintf(buffer, BUFFER_SIZE, "%ld", M); // Convert M to string

        // Write to Pipe A
        write(write_fd, buffer, strlen(buffer) + 1);
    }

    close(read_fd);
    close(write_fd);
    exit(0);
}

/* CWork: Child process function */
void CWork(int read_fd, int write_fd) {
    char buffer[BUFFER_SIZE];
    long M;

    printf("[Child] Ready to proceed. PID: %d\n", getpid());

    while (1) {
        // Read value from Pipe A
        read(read_fd, buffer, BUFFER_SIZE);
        M = atol(buffer); // Convert string to long integer

        // Print current value of M
        printf("[Child] Value = %ld\n", M);

        // Check if M is out of the bounds
        if (M < M_MIN || M > M_MAX) {
            break;
        }

        // Update M
        M = 7 * M - 6;
        snprintf(buffer, BUFFER_SIZE, "%ld", M); // Convert M to string

        // Write to Pipe B
        write(write_fd, buffer, strlen(buffer) + 1);
    }

    close(read_fd);
    close(write_fd);
    exit(0);
}

/* GWork: Grandchild process function */
void GWork(int read_fd, int write_fd) {
    char buffer[BUFFER_SIZE];
    long M;

    printf("[Grandchild] Ready to proceed. PID: %d\n", getpid());

    while (1) {
        // Read value from Pipe B
        read(read_fd, buffer, BUFFER_SIZE);
        M = atol(buffer); // Convert string to long integer

        // Print current value of M
        printf("[Grandchild] Value = %ld\n", M);

        // Check if M is out of the bounds
        if (M < M_MIN || M > M_MAX) {
            break;
        }

        // Update M
        M = 30 - 4 * M;
        snprintf(buffer, BUFFER_SIZE, "%ld", M); // Convert M to string

        // Write to Pipe C
        write(write_fd, buffer, strlen(buffer) + 1);
    }

    close(read_fd);
    close(write_fd);
    exit(0);
}

/* main: main program which creates child and grandchild processes */
int main() {
    int pipeA[2], pipeB[2], pipeC[2];

    /* 1. Create pipes */
    if (pipe(pipeA) == -1) {
        perror("Pipe A error");
        exit(-5);
    }
    if (pipe(pipeB) == -1) {
        perror("Pipe B error");
        exit(-5);
    }
    if (pipe(pipeC) == -1) {
        perror("Pipe C error");
        exit(-5);
    }

    /* 2. Create processes */
    pid_t pid1 = fork();
    if (pid1 < 0) {
        perror("Fork #1 error");
        exit(-5);
    }

    if (pid1 == 0) { // Child process
        pid_t pid2 = fork();
        if (pid2 < 0) {
            perror("Fork #2 error");
            exit(-5);
        }

        if (pid2 == 0) { // Grandchild process
            close(pipeA[0]);
            close(pipeA[1]);
            close(pipeB[1]);
            close(pipeC[0]);
            GWork(pipeB[0], pipeC[1]);
        } else { // Child process
            close(pipeA[1]);
            close(pipeB[0]);
            close(pipeC[0]);
            close(pipeC[1]);
            CWork(pipeA[0], pipeB[1]);
            wait(NULL); // Wait for grandchild to terminate
            exit(0);
        }
    } else { // Parent process
        close(pipeA[0]);
        close(pipeB[0]);
        close(pipeB[1]);
        close(pipeC[1]);
        PWork(pipeC[0], pipeA[1]);
        wait(NULL); // Wait for child to terminate
        return 0;
    }
}

