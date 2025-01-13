#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    // Command and arguments
    char *cmd[] = {"ls", "-l", NULL};
    
    // Execute the command
    if (execvp(cmd[0], cmd) == -1) {
        perror("execvp failed"); 
        exit(EXIT_FAILURE);
    }

    return 0; 
}

