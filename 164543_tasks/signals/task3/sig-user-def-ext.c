/* REQUIRED HEADER FILES */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include<errno.h>
/*my_sigaction: User-defined signal action function */
void my_sigaction(int sig, siginfo_t *info, void *context) {
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
    /* Configure sa_sigaction to use our custom handler */
    sa.sa_sigaction = my_sigaction;
    sa.sa_flags = SA_SIGINFO; /* Use the sa_sigaction interface */
    sigemptyset(&sa.sa_mask); /* No additional blocked signals */
    
 if (sigaction(sig, &sa, NULL) == -1) {
            fprintf(stderr, "sigaction: Unable to handle signal %d\n", sig);
        }
}    

    /* Keep the program running */
    while (1) {
        pause(); // Wait for a signal
    }

    return 0;
}

