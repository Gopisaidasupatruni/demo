#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    int pipefd[2];  // File descriptors for the pipe
    pid_t pid1, pid2;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Create the first child process (left-hand process: "echo foo")
    if ((pid1 = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        // In child 1
        close(pipefd[0]);            // Close read end of the pipe
        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to pipe write-end
        close(pipefd[1]);            // Close original write-end descriptor

        execlp("echo", "echo", "foo", NULL);
        perror("execlp echo");
        exit(EXIT_FAILURE);
    }

    // Create the second child process (right-hand process: "wc -c")
    if ((pid2 = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        // In child 2
        close(pipefd[1]);            // Close write end of the pipe
        dup2(pipefd[0], STDIN_FILENO); // Redirect stdin to pipe read-end
        close(pipefd[0]);            // Close original read-end descriptor

        execlp("wc", "wc", "-c", NULL);
        perror("execlp wc");
        exit(EXIT_FAILURE);
    }

    // In parent
    close(pipefd[0]); // Close both ends of the pipe
    close(pipefd[1]);

    // Wait for both children to terminate
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}

