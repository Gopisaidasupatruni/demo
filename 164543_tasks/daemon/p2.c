#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void create_daemon() {
    pid_t pid;

    
    pid = fork();

    if (pid < 0) {
        /* Fork failed */
        exit(1);
    }

    if (pid > 0) {
        /* Parent process, exit to allow the child to run in the background */
        exit(0);
    }

    /* Child process becomes session leader */
    if (setsid() < 0) {
        exit(1);
    }

    // Fork again to ensure that the daemon is not a session leader
    pid = fork();

    if (pid < 0) {
        exit(1);
    }

    if (pid > 0) {
        // Parent process of the second fork, exit
        exit(0);
    }

    // Change file mode mask
    umask(0);

    // Change working directory to root to avoid blocking filesystems
    chdir("/home/gopisai/c/daemon");

    // Close all open file descriptors (stdin, stdout, stderr)
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    FILE*fp=fopen("file","w");
    // Daemon is now running in the background
    while (1) {
        // Daemon logic here, e.g., write to a log file
        sleep(5);
      fprintf(fp,"Daemon Governred me \n");
fflush(fp);      // Sleep for 10 seconds
    }
    fclose(fp);
}

int main() {
    create_daemon();

    return 0;
}

