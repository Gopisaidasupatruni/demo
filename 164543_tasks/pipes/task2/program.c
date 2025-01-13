#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/wait.h>

void correct_foreground_pipeline(const char* cmd1, char* const* argv1, const char* cmd2, char* const* argv2) {
    int pipefd[2], status;

    /* Step [A]: Set up the pipe */
    if (pipe(pipefd) == -1) {
        perror("Pipe failed");
        exit(EXIT_FAILURE);
    }

    /* Step [B]: Fork the first child process (cmd1) */
    pid_t child1 = fork();
    if (child1 == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (child1 == 0) { // First child process (cmd1)
        /* Redirect stdout to the write end of the pipe */
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);  // Close the unused read end
        close(pipefd[1]);  // Close the original write end

        execvp(cmd1, argv1);  // Execute cmd1
        perror("execvp for cmd1 failed");
        exit(EXIT_FAILURE);   // Exit if execvp fails
    }
    assert(child1 > 0);

    /* Step [C]: Close the write end of the pipe in the parent process */
    close(pipefd[1]);

    /* Step [D]: Fork the second child process (cmd2) */
    pid_t child2 = fork();
    if (child2 == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (child2 == 0) { // Second child process (cmd2)
        /* Redirect stdin to the read end of the pipe */
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);  // Close the original read end

        execvp(cmd2, argv2);  // Execute cmd2
        perror("execvp for cmd2 failed");
        exit(EXIT_FAILURE);   // Exit if execvp fails
    }
    assert(child2 > 0);

    /* Step [E]: Close the read end of the pipe in the parent and wait for both children to complete */
    close(pipefd[0]);
    waitpid(child1, &status, 0);
    waitpid(child2, &status, 0); 
}

int main() {
    // Example commands for testing: "ls -l" | "grep main"
    const char* cmd1 = "ls";
    char* const argv1[] = {"ls", "-l", NULL};

    const char* cmd2 = "grep";
    char* const argv2[] = {"grep", "main", NULL};

    printf("Running pipeline: %s | %s\n", cmd1, cmd2);
    correct_foreground_pipeline(cmd1, argv1, cmd2, argv2);

    return 0;
}

