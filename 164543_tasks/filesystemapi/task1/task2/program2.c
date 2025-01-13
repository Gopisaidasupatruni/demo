#include<stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include<string.h>
int main() 
{
    int fd, ret;
    char ch[10];

    fd = open("file1.txt", O_RDONLY);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    ret = read(fd, ch, 5);
    if (ret < 0) {
        perror("read");
        close(fd); 
        exit(1);
    }

    ch[ret] = '\0';
    close(fd);
     fd = open("file2.txt", O_WRONLY);
    if (fd < 0) {
        perror("open");
        exit(1);
    }
    
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
