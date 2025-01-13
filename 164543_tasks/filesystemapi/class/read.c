#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int fd, ret;
    char ch[10];

    // Open file in read-only mode
    fd = open("mypipe", O_RDONLY);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    // Read up to 5 bytes from the file
    ret = read(fd, ch, 5);
    if (ret < 0) {
        perror("read");
        close(fd); // Close file descriptor before exiting
        exit(1);
    }

    // Add null terminator to ensure correct printing as a string
    ch[ret] = '\0';

    // Print the read content
    printf("read %s", ch);

    // Close the file descriptor
    close(fd);
    return 0;
}

