/* REQUIRED HEADER FILES */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int sig;
    struct sigaction sa;

   
    for (sig = 1; sig < NSIG; sig++) {
	     if (sig == SIGKILL || sig == SIGSTOP) {
            continue;
        }
        /* Set flags for the sigaction structure */
        sa.sa_flags = 0;

        /* Set the handler to SIG_IGN to ignore the signal */
        sa.sa_handler = SIG_IGN;

        /* Clear the signal mask to ensure no signals are blocked */
        sigemptyset(&sa.sa_mask);

        /* Apply the sigaction to the current signal */
        if (sigaction(sig, &sa, NULL) == -1) {
           
            perror("sigaction");
        }
    }

    /* Keep the program running for 30 seconds regardless of signals */
    printf("Ignoring most signals for 30 seconds. Try sending signals during this time.\n");
    int delay = 30; // Initial delay
    while (delay != 0) {
        delay = sleep(delay); 
    }

    printf("Exiting program after 30 seconds.\n");
    return 0;
}

