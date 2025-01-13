
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

void print_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char buffer[BUFFER_SIZE];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        if (fwrite(buffer, 1, bytes_read, stdout) < bytes_read) {
            perror("Error writing to stdout");
            fclose(file);
            return;
        }
    }

   
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc == 1) { 
        print_file(NULL);
    } else {
        for (int i = 1; i < argc; i++) {
            print_file(argv[i]);
        }
    }
    return 0;
}

