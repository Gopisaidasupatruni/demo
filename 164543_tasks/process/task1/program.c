/** Required header files */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Main Program : To perform opeartions on process using fork system call */
int main() {
    /* 1. Print message identifying the original process */
    printf("Original process - PID: %d, Parent's PID: %d\n", getpid(), getppid());

    /* 2. Call fork() and handle first fork */
    printf("About to call fork() for the first time...\n");
    pid_t pid1 = fork();

    /* 3. Handle first fork failure */
    if (pid1 < 0) {
        printf("The first fork failed.\n");
        exit(-1);
    }

    if (pid1 == 0) { 
        /* 4(a). Print message identifying the child */
        printf("Child process - PID: %d, Parent's PID: %d\n", getpid(), getppid());

        /* 4(b). Call second fork */
        printf("About to call fork() for the second time...\n");
        pid_t pid2 = fork();

        /* 4(c). Handle second fork failure */
        if (pid2 < 0) {
            printf("The second fork failed.\n");
            exit(-1);
        }

        if (pid2 == 0) { /* Grandchild process */
            /* 4(d)(i). Print message identifying the grandchild */
            printf("Grandchild process - PID: %d, Parent's PID: %d\n", getpid(), getppid());

            /* 4(d)(ii). Sleep for 3 seconds */
            sleep(3);

            /* 4(d)(iii). Print message about becoming an orphan */
            printf("Grandchild should now be an orphan - PID: %d, Parent's PID: %d\n", getpid(), getppid());

            /* 4(d)(iv). Execute "ps" command */
            printf("Grandchild is about to execute 'ps' command...\n");
            system("ps");

            /* 4(d)(vi). Print exit message */
            printf("Grandchild is about to exit.\n");

            /* 4(d)(vii). Exit with status 0 */
            exit(0);
        } else { /*(second fork) */
            /* 4(e)(i). Print message identifying the child */
            printf("Child process (after second fork) - PID: %d, Parent's PID: %d\n", getpid(), getppid());

            /* 4(e)(ii). Sleep for 2 seconds */
            sleep(2);

            /* 4(e)(iii). Print exit message */
            printf("Child process is about to exit.\n");

            /* 4(e)(iv). Exit with status 0 */
            exit(0);
        }
    } else { /* Parent process */
        /* (a) Print message identifying the parent */
        printf("Parent process - PID: %d, Parent's PID: %d\n", getpid(), getppid());

        /* (b) Sleep for 2 seconds */
        sleep(2);

        /* (c) Print message about calling ps */
        printf("Parent is about to call 'ps' - child should appear as a zombie.\n");

        /* (d) Execute "ps" command */
        system("ps");

        /* (e) Sleep for 3 seconds */
        sleep(3);

        /* (f) Wait for the child to terminate */
        wait(0);

        /* (g) Print message about calling ps again */
        printf("Parent waited on the child and is now calling 'ps' again.\n");

        /* (h) Execute "ps" command */
        system("ps");

        /* (i) Print exit message */
        printf("Parent is about to terminate.\n");

        /* Exit with status 0 */
        exit(0);
    }

    return 0;
}

