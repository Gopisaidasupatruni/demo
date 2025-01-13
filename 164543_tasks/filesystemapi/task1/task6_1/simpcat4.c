#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char **argv) {
    int bufsize;
    char *c;
    int i;

    // Convert buffer size argument from string to integer
    bufsize = atoi(argv[1]);
    c = malloc(bufsize * sizeof(char));

    i = 1;
    while (i > 0) {
        i = read(0, c, bufsize);       // Reading with specified buffer size
        if (i > 0) write(1, c, i);     // Writing the read bytes to output
    }

    free(c);  // Free allocated memory
    return 0;
}

