#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include<string.h>
int main() {
    int fd, ret;
    char ch[10];

    // Open file in read-only mode
    fd = open("file1.txt", O_WRONLY);
    if (fd < 0) {
        perror("open");
        exit(1);
    }
    printf("enter data");
    scanf("%s",ch);
    // Read up to 5 bytes from the file
    ret = write(fd, ch, strlen(ch));
    if (ret < 0) {
        perror("write");
        close(fd); // Close file descriptor before exiting
        exit(1);
    }

    printf("data written");

    // Close the file descriptor
    close(fd);
    return 0;
}

