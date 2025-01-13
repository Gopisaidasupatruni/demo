/* REQUIRED HEADER FILES */ 
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include<errno.h>
/* my_handler : User-defined signal handler */
void my_handler(int sig) {
    printf("Enter signal handler %d\n", sig);
    sleep(3); 
    printf("Leave signal handler %d\n", sig);
}

/* main: to call user defined signal handler */
int main(int argc, char *argv[]) {
    int sig;
    struct sigaction sa;

    /* Set up the user-defined handler for most signals */
    for (sig = 1; sig < NSIG; sig++) {
        sa.sa_handler = my_handler;
        sa.sa_flags = 0;            /* Default flags */
        sigemptyset(&sa.sa_mask);   /* No blocked signals during handler execution */

        /* Attempt to set the signal action */
        if (sigaction(sig, &sa, NULL) == -1) {
            perror("sigaction"); 
	}
    }

    printf("Handling signals for 30 seconds. Try sending signals.\n");

    /* Keep the program running for 30 seconds */
    int delay = 30;
    while (delay != 0) delay = sleep(delay);

    printf("Exiting program after 30 seconds.\n");
    return 0;
}

