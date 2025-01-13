#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

// Function to mimic cat using system calls
void cat_with_syscalls(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;

    while ((bytesRead = read(fd, buffer, BUFFER_SIZE)) > 0) {
        if (write(STDOUT_FILENO, buffer, bytesRead) != bytesRead) {
            perror("Error writing to stdout");
            break;
        }
    }

    if (bytesRead < 0) {
        perror("Error reading from file");
    }

    close(fd);
}

// Function to mimic cat using standard I/O library
void cat_with_stdio(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (putchar(ch) == EOF) {
            perror("Error writing to stdout");
            break;
        }
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    printf("=== Output using system calls ===\n");
    cat_with_syscalls(argv[1]);

    printf("\n=== Output using standard I/O ===\n");
    cat_with_stdio(argv[1]);

    return 0;
}

