#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024  // Define a buffer size for reading chunks

int main(int argc, char *argv[]) {
    int src_fd, dest_fd, ret;
    char buffer[BUFFER_SIZE];

    // Check if the correct number of arguments is provided
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Open the source file in read-only mode
    src_fd = open(argv[1], O_RDONLY);
    if (src_fd < 0) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    // Open the destination file in write-only mode, create if it doesn't exist, truncate if it does
    dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd < 0) {
        perror("Error opening destination file");
        close(src_fd);  // Close the source file before exiting
        exit(EXIT_FAILURE);
    }

    // Copy contents from source to destination in chunks
    while ((ret = read(src_fd, buffer, BUFFER_SIZE)) > 0) {
        if (write(dest_fd, buffer, ret) != ret) {
            perror("Error writing to destination file");
            close(src_fd);
            close(dest_fd);
            exit(EXIT_FAILURE);
        }
    }

    // Check if there was an error while reading
    if (ret < 0) {
        perror("Error reading from source file");
    }

    printf("File copied successfully.\n");

    // Close both files
    close(src_fd);
    close(dest_fd);
    return 0;
}

