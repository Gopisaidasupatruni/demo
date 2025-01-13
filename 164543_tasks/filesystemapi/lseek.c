#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int fd;
    char buffer[20];

    fd = open("file1.txt", O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    // Read and print the first 10 bytes of the file
    read(fd, buffer, 10);
    buffer[10] = '\0';
    printf("First 10 bytes: %s\n", buffer);

    // Use lseek to move the file pointer to 5 bytes from the beginning
    lseek(fd, 5, SEEK_SET);
    
    // Write "HELLO" at this position
    write(fd, "HELLO", 5);

    // Move the pointer to 5 bytes 
    lseek(fd, -10, SEEK_CUR);

    // Read the last 5 bytes of the file
    read(fd, buffer, 10);
    buffer[10] = '\0';
    printf("10 bytes: %s\n", buffer);

    // Close the file
    close(fd);
    return 0;
}

