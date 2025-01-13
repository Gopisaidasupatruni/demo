/* Required header files */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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

        // Close both ends of the pipe as they're not used in this process
        close(pipefd[0]);
        close(pipefd[1]);

        // Execute "echo foo", which will output directly to the shell's stdout
        execlp("echo", "echo", "foo", NULL);
        
        // If exec fails
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    // Close the write end of the pipe in the parent, so wc will read EOF
    close(pipefd[1]);

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

        // Close both ends of the pipe as they're no longer needed
        close(pipefd[0]);

        // Execute "wc -c", which will receive no input and output "0"
        execlp("wc", "wc", "-c", NULL);

        // If exec fails
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    // Close the read end of the pipe in the parent
    close(pipefd[0]);

    // Wait for both child processes to complete
    waitpid(child1, NULL, 0);
    waitpid(child2, NULL, 0);

    return 0;
}

