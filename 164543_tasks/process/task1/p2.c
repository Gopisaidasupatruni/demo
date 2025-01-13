#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    // Step 1: Print message identifying the original process
    printf("Original process - PID: %d, Parent's PID: %d\n", getpid(), getppid());

    // Step 2: Call fork() after printing a message
    printf("About to call fork() for the first time...\n");
    pid_t pid1 = fork();

    // Step 3: Handle first fork failure
    if (pid1 < 0) {
        printf("The first fork failed.\n");
        exit(-1);
    }

    if (pid1 == 0) { // Child process
        // Step 4a: Print message identifying the child process
        printf("Child process - PID: %d, Parent's PID: %d\n", getpid(), getppid());

        // Step 4b: Call fork() again in the child process
        printf("About to call fork() for the second time...\n");
        pid_t pid2 = fork();

        // Step 4c: Handle second fork failure
        if (pid2 < 0) {
            printf("The second fork failed.\n");
            exit(-1);
        }

        if (pid2 == 0) { // Grandchild process
            // Step 4d(i): Print message identifying the grandchild process
            printf("Grandchild process - PID: %d, Parent's PID: %d\n", getpid(), getppid());

            // Step 4d(ii): Sleep for 3 seconds
            sleep(3);

            // Step 4d(iii): Print message about being an orphan
            printf("Grandchild process should now be an orphan - PID: %d, Parent's PID: %d\n", getpid(), getppid());

            // Step 4d(iv): Execute "ps" command
            printf("Grandchild process is about to execute 'ps' command...\n");
            system("ps");

            // Step 4d(v): Print exit message
            printf("Grandchild process is about to exit.\n");

            // Step 4d(vi): Exit with status 0
            exit(0);
        } else { // Child process (after second fork)
            // Step 4e(i): Print message identifying the child process
            printf("Child process (after second fork) - PID: %d, Parent's PID: %d\n", getpid(), getppid());

            // Step 4e(ii): Sleep for 2 seconds
            sleep(2);

            // Step 4e(iii): Print exit message
            printf("Child process is about to exit.\n");

            // Step 4e(iv): Exit with status 0
            exit(0);
        }
    } else { // Parent process
        // Parent process doesn't need to do anything further
        sleep(5); // Allow child and grandchild to complete
    }

    return 0;
}

