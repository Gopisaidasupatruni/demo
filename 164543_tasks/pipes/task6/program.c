/*This program is to figure out what code to add at points A, B, and C. in code below */
/* Required header files */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <assert.h>

struct command {
    struct command *next;  
    int argc;              
    int ispipe;            
    char **argv;           
    pid_t pid;             
};

/* Function prototype */
void do_pipes(struct command* c);

/* create_command: Function to create and initialize a command structure */
struct command* create_command(char **argv, int ispipe) {
    struct command *cmd = (struct command*)malloc(sizeof(struct command));
    cmd->argc = 0;
    while (argv[cmd->argc] != NULL) {
        cmd->argc++;
    }
    cmd->argv = argv;
    cmd->ispipe = ispipe;
    cmd->next = NULL;
    return cmd;
}
/* main: passing commands with pipes */
int main() {
    /* Define arguments for each command in the pipeline */
    char *argv1[] = {"ls", NULL};
    char *argv2[] = {"grep", "txt", NULL};
    char *argv3[] = {"wc", "-l", NULL};

    /* Create command structures */
    struct command *cmd1 = create_command(argv1, 1); /* pipe after "ls" */
    struct command *cmd2 = create_command(argv2, 1); /* pipe after "grep txt" */
    struct command *cmd3 = create_command(argv3, 0); /* no pipe after "wc -l" */

    /* Link the commands to form a pipeline*/
    cmd1->next = cmd2;
    cmd2->next = cmd3;

    /* Execute the pipeline */
    do_pipes(cmd1);

    /* Wait for all child processes to finish */
    struct command *cmd = cmd1;
    while (cmd != NULL) {
        waitpid(cmd->pid, NULL, 0); /* Wait for each process in the pipeline */
        cmd = cmd->next;
    }

    /* Free allocated memory */
    free(cmd1);
    free(cmd2);
    free(cmd3);

    return 0;
}

void do_pipes(struct command* c) {
   pid_t newpid;
   int havepipe = 0;          /* Tracks if the previous command had a pipe */
   int lastpipe[2] = {-1, -1}; /* Stores the FDs of the last pipe created */
   int curpipe[2];             /* Stores the FDs of the current pipe */

   do {
       /* Create a new pipe if the current command has a pipe */
       if (c->ispipe) {
           int r = pipe(curpipe);
           assert(r == 0); 
       }

       /* Fork a new process to execute the command */
       newpid = fork();
       assert(newpid >= 0); 

       /* If we're in the child process */
       if (newpid == 0) {
           // **** PART A: Hook up input from the previous command's pipe ****
           if (havepipe) {
               close(0);             
	       dup2(lastpipe[0], 0);   
               close(lastpipe[0]);      
               close(lastpipe[1]);     
 	   }

           // **** PART B: Hook up output to the next command's pipe ****
           if (c->ispipe) {
               close(1);             
	       dup2(curpipe[1], 1);   
               close(curpipe[1]);     
               close(curpipe[0]);     
           }

           // Execute the command with execvp
           execvp(c->argv[0], c->argv);

           // If execvp fails, print an error and exit the child process
           fprintf(stderr, "Exec failed\n");
           _exit(1);
       }

       // **** PART C: Close pipe ends in the parent process ****
       if (havepipe) {
           close(lastpipe[0]); // Close both ends of lastpipe in the parent
           close(lastpipe[1]);
       }

       /* Set up for the next command */
       havepipe = c->ispipe; // Track if this command has a pipe
       if (c->ispipe) {
           lastpipe[0] = curpipe[0];
           lastpipe[1] = curpipe[1];
       }
       c->pid = newpid; // Save the PID of the forked process
       c = c->next;     // Move to the next command
   } while (newpid != -1 && havepipe);
}

