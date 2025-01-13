/** Required header files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/** Macro definitions */
#define MAX_CMD_LENGTH 1024
#define MAX_ARGS 100

int main() {
    char input[MAX_CMD_LENGTH]; 
    char *args[MAX_ARGS];  
    char *cmd1[MAX_ARGS], *cmd2[MAX_ARGS];
    int pipefd[2];                    
    pid_t pid1, pid2;                 /* Process IDs for forked processes */

    while (1) {
        /* Print the prompt */
        printf("EIC> ");

        /* Read the input from the user */
        if (!fgets(input, MAX_CMD_LENGTH, stdin)) {
            perror("fgets");
            exit(1);
        }


        input[strcspn(input, "\n")] = 0;
        /* If the user types "quit" or "q", exit the shell */
        if (strcmp(input, "quit") == 0 || strcmp(input, "q") == 0) {
            printf("Exiting shell...\n");
            break;
        }

        /* Check for pipe ("||") in the input */
        char *pipe_pos = strstr(input, "||");
        if (pipe_pos != NULL) { 
            *pipe_pos = '\0'; 
            char *cmd1_str = input;   
            char *cmd2_str = pipe_pos + 2;  

            /* Tokenize the first command into arguments */
            int i = 0;
            cmd1[i] = strtok(cmd1_str, " ");
            while (cmd1[i] != NULL) {
                cmd1[++i] = strtok(NULL, " ");
            }

            /* Tokenize the second command into arguments */
            i = 0;
            cmd2[i] = strtok(cmd2_str, " ");
            while (cmd2[i] != NULL) {
                cmd2[++i] = strtok(NULL, " ");
            }

            /* Create the pipe */
            if (pipe(pipefd) == -1) {
                perror("pipe");
                continue;
            }

            /* Fork the first child process */
            if ((pid1 = fork()) == -1) {
                perror("fork");
                exit(1);
            }

            if (pid1 == 0) { /* Child process for the first command */
                close(pipefd[0]); 
                dup2(pipefd[1], STDOUT_FILENO); 
                close(pipefd[1]); 

                /* Execute the first command */
                if (execvp(cmd1[0], cmd1) == -1) {
                    perror("execvp");
                    exit(1);
                }
            }

            /* Fork the second child process */
            if ((pid2 = fork()) == -1) {
                perror("fork");
                exit(1);
            }

            if (pid2 == 0) { /* Child process for the second command */
                close(pipefd[1]);
                dup2(pipefd[0], STDIN_FILENO); 
                close(pipefd[0]); 

                /* Execute the second command */
                if (execvp(cmd2[0], cmd2) == -1) {
                    perror("execvp");
                    exit(1);
                }
            }

            /* Parent process: Close both ends of the pipe and wait for children */
            close(pipefd[0]);
            close(pipefd[1]);
            waitpid(pid1, NULL, 0);
            waitpid(pid2, NULL, 0);

        } else { /* Input does not contain a pipe */
            /* Tokenize the input into arguments */
            int i = 0;
            args[i] = strtok(input, " ");
            while (args[i] != NULL) {
                args[++i] = strtok(NULL, " ");
            }

            /* Fork a child process */
            if ((pid1 = fork()) == -1) {
                perror("fork");
                exit(1);
            }

            if (pid1 == 0) { 
                /* Execute the command */
                if (execvp(args[0], args) == -1) {
                    perror("execvp");
                    exit(1);
                }
            } else { 
                /* Wait for the child to finish */
                waitpid(pid1, NULL, 0);
            }
        }
    }

    return 0;
}
/* End main */
