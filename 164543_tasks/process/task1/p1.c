/* Task1 
 * Your executable file should be named Process Task1. It should do the following:

 

1. Print a message identifying the process as the original process and providing its PID and its parent's PID.

 

2. Call fork() after printing a message saying you are about to do so.

 

3. If fork() fails, print an error message ("The first fork failed.") and exit with a status of -1.

 

4. If fork() succeeds, we now have two processes: parent and child.
*/
/** Required header files */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/* main:  process using fork*/
int main() {
    /* print the message identifying the original process */
    printf("Original process - PID: %d, Parent's PID: %d\n", getpid(), getppid());

    printf("About to call fork() for the first time...\n");

    /* First fork to create a child process */
    pid_t pid1 = fork();

    /* If fork fails, print an error message and exit */
    if (pid1 < 0) {
        printf("The first fork failed.\n");
        exit(-1); 
    }

    /* if we are in the child process (pid1 == 0) **/
    if (pid1 == 0) {
        
        printf("Child process - PID: %d, Parent's PID: %d\n", getpid(), getppid());

        
        printf("About to call fork() for the second time...\n");

        /* Second fork to create a grandchild process */
        pid_t pid2 = fork();

        /* If fork fails, print an error message and exit */
        if (pid2 < 0) {
            printf("The second fork failed.\n");
            exit(-1); 
        }

        /* If we are in the grandchild process (pid2 == 0) */
        if (pid2 == 0) {
            /* Print a message identifying the grandchild process */
            printf("Grandchild process - PID: %d, Parent's PID: %d\n", getpid(), getppid());
        }
    }

    
    return 0; 
}

