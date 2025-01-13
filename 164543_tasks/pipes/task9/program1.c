#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipefd[2]; // Pipe file descriptors
    pid_t pid1, pid2;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork the first child (echo foo)
    if ((pid1 = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        // In child 1
        close(pipefd[0]);            // Close read end of pipe
        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to pipe write end
        close(pipefd[1]);            // Close unused write descriptor
        execlp("echo", "echo", "foo", NULL);
        perror("execlp echo");
        exit(EXIT_FAILURE);
    }

    // Fork the second child (wc -c)
    if ((pid2 = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        // In child 2
        close(pipefd[1]);            // Close write end of pipe
        dup2(pipefd[0], STDIN_FILENO); // Redirect stdin to pipe read end
        close(pipefd[0]);            // Close unused read descriptor
        execlp("wc", "wc", "-c", NULL);
        perror("execlp wc");
        exit(EXIT_FAILURE);
    }

    // In parent process
    close(pipefd[0]); // Close both ends of the pipe
    close(pipefd[1]);

    // Wait for both child processes (CORRECT)
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}

