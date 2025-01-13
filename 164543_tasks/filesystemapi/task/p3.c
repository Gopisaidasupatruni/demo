#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

#define LOG_FILE "/home/gopisai/linux_fun/task1/logfile"

void write_to_fill_log(const char *source) {
    char *username;
    long t;
    int fd;
    char buffer[256];

    username = getenv("USER");
    if (username == NULL) {
        fprintf(stderr, "Error: Could not retrieve USER environment variable.\n");
        return;
    }

    t = time(NULL);
    
    fd = open(LOG_FILE, O_WRONLY | O_APPEND | O_SYNC, 0644);
    if (fd == -1) {
        perror("Error opening log file");
        return;
    }

    snprintf(buffer, sizeof(buffer), "%s %ld in %s\n", username, t, source);

    if (write(fd, buffer, strlen(buffer)) == -1) {
        perror("Error writing to log file");
    }

    close(fd);
}

int main() {
    int n = 10;
    while (n != 0) {
        write_to_fill_log("file1"); 

        sleep(1);
        n--;
    }
}

