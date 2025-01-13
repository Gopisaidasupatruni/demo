/* Required header files */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/wait.h>

void simple_pipe(const char* cmd1, char* const* argv1, const char* cmd2, char* const* argv2) {
    int pipefd[2], status;

    /* A : Set up the pipe */
    if (pipe(pipefd) == -1) {
        perror("Pipe failed");
        exit(EXIT_FAILURE);
    }

    /* B : Set up the first child process (cmd1) */
    pid_t child1 = fork();
    if (child1 == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (child1 == 0) { /* Child process for cmd1 */
        /* Redirect stdout to the write end of the pipe */
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);  /* Close unused read end */
        close(pipefd[1]);  /* Close original write end */

        execvp(cmd1, argv1);  
        perror("execvp for cmd1 failed");
        exit(1);   
    }
    assert(child1 > 0);

    /* C: Close the write end of the pipe in the parent */
    close(pipefd[1]);

    /* D: Set up the second child process (cmd2) */
    pid_t child2 = fork();
    if (child2 == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (child2 == 0) { /* Child process for cmd2 */
        /* Redirect stdin to the read end of the pipe */
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);  /* Close original read end */

        execvp(cmd2, argv2);  
        perror("execvp for cmd2 failed");
        exit(1);   
    }
    assert(child2 > 0);

    /* E: Close the read end of the pipe in the parent and wait for both children */
    close(pipefd[0]);
    waitpid(child1, &status, 0); 
    waitpid(child2, &status, 0); 
}
/* main : using simple pipe */
int main() {
    /* Example commands: "ls -l" | "grep main" */
    const char* cmd1 = "ls";
    char* const argv1[] = {"ls", "-l", NULL};

    const char* cmd2 = "grep";
    char* const argv2[] = {"grep", "main", NULL};

    printf("Running : %s | %s\n", cmd1, cmd2);
    simple_pipe(cmd1, argv1, cmd2, argv2);

    return 0;
}

