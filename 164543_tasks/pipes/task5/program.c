/* REQUIRED HEADER FILES */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pid_t child1, child2;

    /* Create the pipe */
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    child1 = fork();
    if (child1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child1 == 0) {

        // Redirect stdout to the write end of the pipe
        dup2(pipefd[1], STDOUT_FILENO);

        // Close both ends of the pipe in this child
        close(pipefd[0]);
        close(pipefd[1]);

        execlp("yes", "yes", "A", NULL);

    //for (int i = 0; i < 1048580; i++) {
      //  write(STDOUT_FILENO, "A", 1);
    //}
   // exit(EXIT_SUCCESS);


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

        /* Redirect stdin to the read end of the pipe */
        dup2(pipefd[0], STDIN_FILENO);

        // Close both ends of the pipe in this child
        close(pipefd[0]);
        close(pipefd[1]);

        // Adding a delay to simulate slow reading
        for (int i = 0; i < 100; i++) {
            sleep(1);  // Simulate slow processing
        }

        // Execute "wc -c"
        execlp("wc", "wc", "-c", NULL);

        // If exec fails
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    // Parent process: close both ends of the pipe
    close(pipefd[0]);
    close(pipefd[1]);

    // Wait for both child processes to complete
    waitpid(child1, NULL, 0);
    waitpid(child2, NULL, 0);

    return 0;
}

