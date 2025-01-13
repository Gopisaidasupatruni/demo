#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv) {
    int bufsize;
    char *c;
    int i;

    // Convert buffer size argument from string to integer
    bufsize = atoi(argv[1]);
    c = malloc(bufsize * sizeof(char));

    i = 1;
    while (i > 0) {
        i = fread(c, 1, bufsize, stdin);    // Buffered read with specified buffer size
        if (i > 0) fwrite(c, 1, i, stdout); // Buffered write to output
    }

    free(c);  // Free allocated memory
    return 0;
}

