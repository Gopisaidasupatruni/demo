#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    int sig;
    struct sigaction sa;

    printf("Ignoring most signals for 30 seconds. Try sending signals during this time.\n");

    for (sig = 1; sig < NSIG; sig++) { // Iterate through all signals
        // Set default flags and handler to ignore the signal
        sa.sa_flags = 0;
        sa.sa_handler = SIG_IGN;
        sigemptyset(&sa.sa_mask); // No additional signals blocked during handler execution

        // Attempt to set the action for the signal
        if (sigaction(sig, &sa, NULL) == -1) {
            // Check for errors and print messages
            if (errno == EINVAL) {
                printf("Signal %d cannot be ignored: %s\n", sig, strerror(errno));
            } 
        }
    }

    // Pause for 30 seconds to allow testing
    int delay = 30;
    while (delay != 0) delay = sleep(delay);

    printf("Exiting program after 30 seconds.\n");
    return 0;
}

