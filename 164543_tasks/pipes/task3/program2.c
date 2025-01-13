#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    int pipefd[2];
    pid_t child1, child2;

    // Create the pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork the first child to execute "echo foo"
    child1 = fork();
    if (child1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    
    if (child1 == 0) {
        // First child process (echo foo)
        
        // Redirect stdout to the write end of the pipe
        dup2(pipefd[1], STDOUT_FILENO);

        // Close both ends of the pipe in this child
        close(pipefd[0]);
        close(pipefd[1]);

        // Execute "echo foo"
        execlp("echo", "echo", "foo", NULL);
        
        // If exec fails
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    // Fork the second child to execute "wc -c"
    child2 = fork();
    if (child2 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child2 == 0) {
        // Second child process (wc -c)

        // Redirect stdin to the read end of the pipe
        dup2(pipefd[0], STDIN_FILENO);

        // Close both ends of the pipe in this child
        close(pipefd[0]);
        close(pipefd[1]);

        // Execute "wc -c"
        execlp("wc", "wc", "-c", NULL);

        // If exec fails
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    // Parent process

    // Close the read end of the pipe in the parent
    close(pipefd[0]);

    // Intentionally keep the write end open to prevent "wc" from receiving EOF
    // Comment out the line below if you want `wc` to receive EOF and exit.
   // close(pipefd[1]);

    // Wait for both child processes to complete
    waitpid(child1, NULL, 0);  // Wait for "echo foo" to complete
    // Here, "wc -c" will not complete until the write end of the pipe is closed
    waitpid(child2, NULL, 0);

    // Close the write end after both children are done
    close(pipefd[1]);

    return 0;
}

