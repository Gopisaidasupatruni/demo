 #include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
// User-defined signal handler
void my_handler(int sig) {
    printf("Enter signal handler %d\n", sig);
    sleep(3); // Simulate some work in the handler
    printf("Leave signal handler %d\n", sig);
}

int main(int argc, char *argv[]) {
    int sig;
    struct sigaction sa;

    // Set up the user-defined handler for most signals
    for (sig = 1; sig < NSIG; sig++) {
        // Skip critical signals like SIGKILL (9) and SIGSTOP (19) explicitly
        if (sig == SIGKILL || sig == SIGSTOP) {
            printf("Signal %d cannot have a custom handler (system restriction).\n", sig);
            continue;
        }

   
        sa.sa_handler = my_handler; // Use custom signal handler
        sa.sa_flags = SA_NODEFER;            // Default flags
        sigemptyset(&sa.sa_mask);   // No blocked signals during handler execution

        // Attempt to set the signal action
        if (sigaction(sig, &sa, NULL) == -1) {
            perror("sigaction"); // Report signals that cannot have handlers
        }
    }

    printf("Handling signals for 30 seconds. Try sending signals.\n");

    // Keep the program running for 30 seconds
    int delay = 30;
    while (delay != 0) delay = sleep(delay);

    printf("Exiting program after 30 seconds.\n");
    return 0;
}

