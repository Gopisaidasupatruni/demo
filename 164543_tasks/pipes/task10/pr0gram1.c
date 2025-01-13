#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipefd[2]; // File descriptors for the pipe
    pid_t pid1, pid2;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork the first child (e.g., echo foo)
    if ((pid1 = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        // In the first child
        close(pipefd[0]); // Close unused read end
        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to the pipe
        close(pipefd[1]); // Close pipe write end after redirection
        execlp("echo", "echo", "foo", NULL);
        perror("execlp echo");
        exit(EXIT_FAILURE);
    }

    // Wait for the first child to finish (INCORRECT)
    waitpid(pid1, NULL, 0);

    // Fork the second child (e.g., wc -c)
    if ((pid2 = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        // In the second child
        close(pipefd[1]); // Close unused write end
        dup2(pipefd[0], STDIN_FILENO); // Redirect stdin to the pipe
        close(pipefd[0]); // Close pipe read end after redirection
        execlp("wc", "wc", "-c", NULL);
        perror("execlp wc");
        exit(EXIT_FAILURE);
    }

    // Close pipe in the parent process
    close(pipefd[0]);
    close(pipefd[1]);

    // Wait for the second child to finish
    waitpid(pid2, NULL, 0);

    return 0;
}

