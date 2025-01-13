#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

void my_sigaction(int sig, siginfo_t *info, void *context) {
    printf("Received signal %d\n", sig);
    if (info->si_pid == 0) {
        printf("Signal sent by the terminal (no specific process).\n");
    } else {
        printf("Signal sent by process with PID: %d\n", info->si_pid);
    }
    printf("Finished handling signal %d\n", sig);
}

int main() {
    int sig;
    struct sigaction sa;

    printf("Process PID: %d\n", getpid());
    printf("Handling signals. Send signals to this process using kill or terminal commands.\n");

    for (sig = 1; sig < NSIG; sig++) {
        if (sig == SIGKILL || sig == SIGSTOP) {
            continue; // These signals cannot be caught or ignored.
        }

        sa.sa_sigaction = my_sigaction;
        sa.sa_flags = SA_SIGINFO; // Use sa_sigaction instead of sa_handler
        sigemptyset(&sa.sa_mask);

        if (sigaction(sig, &sa, NULL) == -1) {
            fprintf(stderr, "sigaction: Unable to handle signal %d: %s\n", sig, strerror(errno));
        }
    }

    // Infinite loop to keep the process running and listening for signals
    while (1) {
        pause(); // Wait for signals
    }

    return 0;
}

