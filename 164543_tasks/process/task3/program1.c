#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_CMD_LENGTH 1024
#define MAX_ARGS 100

// Function to split a string by a delimiter
void split_input(char *input, char *delim, char **args) {
    int index = 0;
    char *token = strtok(input, delim);
    
    while (token != NULL) {
        args[index++] = token;
        token = strtok(NULL, delim);
    }
    args[index] = NULL;
}

int main() {
    char input[MAX_CMD_LENGTH];      // Holds user input
    char *args[MAX_ARGS];            // Array to hold command arguments
    char *cmd1[MAX_ARGS], *cmd2[MAX_ARGS]; // Commands for the pipe
    int pipefd[2];                   // Pipe file descriptors
    pid_t pid1, pid2;                // Process IDs for forked processes
    
    while (1) {
        // Print the prompt
        printf("EIC> ");
        
        // Read the input from the user
        if (!fgets(input, MAX_CMD_LENGTH, stdin)) {
            perror("fgets");
            exit(1);
        }
        
        // Remove trailing newline character
        input[strcspn(input, "\n")] = 0;

        // If the user types "quit" or "q", exit the shell
        if (strcmp(input, "quit") == 0 || strcmp(input, "q") == 0) {
            printf("Exiting shell...\n");
            break;
        }

        // Check for pipe ("||") in the input
        char *pipe_pos = strstr(input, "||");
        if (pipe_pos != NULL) {
            *pipe_pos = '\0'; // Terminate the first command
            char *cmd1_str = input;
            char *cmd2_str = pipe_pos + 2; // Skip "||"
            
            // Split the two commands on either side of the pipe
            split_input(cmd1_str, " \t", cmd1);
            split_input(cmd2_str, " \t", cmd2);

            // Create the pipe
            if (pipe(pipefd) == -1) {
                perror("pipe");
                continue;
            }

            // Fork the first child process (for the first command)
            if ((pid1 = fork()) == -1) {
                perror("fork");
                exit(1);
            }

            if (pid1 == 0) {  // Child process for the first command
                // Close the write end of the pipe
                close(pipefd[0]);
                // Redirect stdout to the pipe
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[1]);

                // Execute the first command
                if (execvp(cmd1[0], cmd1) == -1) {
                    perror("execvp");
                    exit(1);
                }
            } else {  // Parent process
                // Fork the second child process (for the second command)
                if ((pid2 = fork()) == -1) {
                    perror("fork");
                    exit(1);
                }

                if (pid2 == 0) {  // Child process for the second command
                    // Close the write end of the pipe
                    close(pipefd[1]);
                    // Redirect stdin to the pipe
                    dup2(pipefd[0], STDIN_FILENO);
                    close(pipefd[0]);

                    // Execute the second command
                    if (execvp(cmd2[0], cmd2) == -1) {
                        perror("execvp");
                        exit(1);
                    }
                } else {  // Parent process
                    // Close both ends of the pipe in the parent
                    close(pipefd[0]);
                    close(pipefd[1]);
                    // Wait for both children to finish
                    waitpid(pid1, NULL, 0);
                    waitpid(pid2, NULL, 0);
                }
            }
        } else {  // No pipe, just a normal command
            // Split the command into arguments
            split_input(input, " \t", args);

            // Fork a child process to execute the command
            if ((pid1 = fork()) == -1) {
                perror("fork");
                exit(1);
            }

            if (pid1 == 0) {  // Child process
                if (execvp(args[0], args) == -1) {
                    perror("execvp");
                    exit(1);
                }
            } else {  // Parent process
                waitpid(pid1, NULL, 0);
            }
        }
    }

    return 0;
}

