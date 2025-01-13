#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_CMD_LENGTH 1024
#define MAX_ARGS 100
#define MAX_PIPES 10

// Function to parse a command string into arguments
void parse_command(char *command, char **args) {
    int i = 0;
    char *token = strtok(command, " ");
    while (token != NULL && i < MAX_ARGS - 1) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;
}

// Function to split input into commands based on pipes
int split_commands(char *input, char **commands) {
    int count = 0;
    char *token = strtok(input, "||");
    while (token != NULL && count < MAX_PIPES + 1) {
        commands[count++] = token;
        token = strtok(NULL, "||");
    }
    return count;
}

int main() {
    char input[MAX_CMD_LENGTH];
    char *commands[MAX_PIPES + 1]; // Array to hold commands split by pipes
    char *args[MAX_ARGS];
    int pipefd[MAX_PIPES][2]; // Array of pipe file descriptors
    pid_t pid;
    int i, num_pipes;

    while (1) {
        printf("EIC> ");
        if (!fgets(input, MAX_CMD_LENGTH, stdin)) {
            perror("fgets");
            exit(1);
        }

        // Remove trailing newline character
        input[strcspn(input, "\n")] = '\0';

        // Exit on "quit" or "q"
        if (strcmp(input, "quit") == 0 || strcmp(input, "q") == 0) {
            printf("Exiting shell...\n");
            break;
        }

        // Split the input into commands
        num_pipes = split_commands(input, commands) - 1;

        // Create pipes
        for (i = 0; i < num_pipes; i++) {
            if (pipe(pipefd[i]) == -1) {
                perror("pipe");
                exit(1);
            }
        }

        // Loop through each command
        for (i = 0; i <= num_pipes; i++) {
            if ((pid = fork()) == -1) {
                perror("fork");
                exit(1);
            }

            if (pid == 0) { // Child process
                // Set up pipe redirection
                if (i > 0) { // Not the first command: read from the previous pipe
                    dup2(pipefd[i - 1][0], STDIN_FILENO);
                }
                if (i < num_pipes) { // Not the last command: write to the next pipe
                    dup2(pipefd[i][1], STDOUT_FILENO);
                }

                // Close all pipe ends
                for (int j = 0; j < num_pipes; j++) {
                    close(pipefd[j][0]);
                    close(pipefd[j][1]);
                }

                // Parse and execute the command
                parse_command(commands[i], args);
                execvp(args[0], args);
                perror("execvp");
                exit(1);
            }
        }

        // Parent process: close all pipe ends and wait for children
        for (i = 0; i < num_pipes; i++) {
            close(pipefd[i][0]);
            close(pipefd[i][1]);
        }
        for (i = 0; i <= num_pipes; i++) {
            wait(NULL);
        }
    }

    return 0;
}

