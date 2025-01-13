/* REQUIRED HEADER FILES */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 10

/* PWork: Parent process function */
void PWork(int read_fd, int write_fd) {
    char buffer[BUFFER_SIZE];

    printf("[Parent] Ready to proceed. PID: %d\n", getpid());

    int num = 1; /* Initial number to start the ring */
    snprintf(buffer, BUFFER_SIZE, "%d", num);
    write(write_fd, buffer, strlen(buffer) + 1); /* Write to Pipe A */

    read(read_fd, buffer, BUFFER_SIZE); // Read from Pipe C
    num = atoi(buffer);
    printf("[Parent] Final number: %d\n", num);

    close(read_fd);
    close(write_fd);
    exit(0);
}

/* CWork: Child process function */
void CWork(int read_fd, int write_fd) {
    char buffer[BUFFER_SIZE];

    printf("[Child] Ready to proceed. PID: %d\n", getpid());

    read(read_fd, buffer, BUFFER_SIZE); // Read from Pipe A
    int num = atoi(buffer); // Convert string to integer
    printf("[Child] Received number: %d\n", num);
    num += 2; // Perform arithmetic
    snprintf(buffer, BUFFER_SIZE, "%d", num); // Convert number to string
    write(write_fd, buffer, strlen(buffer) + 1); // Write to Pipe B

    close(read_fd);
    close(write_fd);
    exit(0);
}

/* GWork: Grandchild process function */
void GWork(int read_fd, int write_fd) {
    char buffer[BUFFER_SIZE];

    printf("[Grandchild] Ready to proceed. PID: %d\n", getpid());

    read(read_fd, buffer, BUFFER_SIZE); // Read from Pipe B
    int num = atoi(buffer); // Convert string to integer
    printf("[Grandchild] Received number: %d\n", num);
    num *= 3; // Perform arithmetic
    snprintf(buffer, BUFFER_SIZE, "%d", num); // Convert number to string
    write(write_fd, buffer, strlen(buffer) + 1); // Write to Pipe C

    close(read_fd);
    close(write_fd);
    exit(0);
}

/* main: main program which creates child and grandchild processes*/
int main() {
    int pipeA[2], pipeB[2], pipeC[2];

    /* 1. Create pipes */
    if (pipe(pipeA) == -1) {
        perror("Pipe A error");
        exit(-1);
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

    if (pid1 == 0) { /* Child process */
        pid_t pid2 = fork();
        if (pid2 < 0) {
            perror("Fork #2 error");
            exit(-5);
        }

        if (pid2 == 0) { /* Grandchild process */
            close(pipeA[0]);
            close(pipeA[1]);
            close(pipeC[1]);
            close(pipeB[0]);
            GWork(pipeC[0], pipeB[1]);
        } else { /* Child process */
            close(pipeA[1]);
            close(pipeB[0]);
            close(pipeC[0]);
            close(pipeB[1]);
            CWork(pipeA[0], pipeC[1]);
            wait(NULL);  
	     exit(0);
        }
    } else { /* Parent process */
        close(pipeA[0]);
        close(pipeC[0]);
        close(pipeB[1]);
        close(pipeC[1]);
        PWork(pipeB[0], pipeA[1]);
        wait(NULL); /* Wait for child to terminate */
        return 0;
    }
}

