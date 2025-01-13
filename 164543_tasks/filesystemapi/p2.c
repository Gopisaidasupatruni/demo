#include <stdio.h>
//#define NDEBUG
#include <assert.h>
#include <string.h>

void checkerror_strcpy(char *src, char *dst) {
    assert(strcmp(src , dst)!=0);    // Ensure source and destination are not the same
    assert(src != NULL);   // Ensure source is not NULL
    assert(dst != NULL);   // Ensure destination is not NULL
    strcpy(dst, src);      // Proceed with copying if all assertions pass
}

int main() {
    char src[] = "Hello, World!";
    char dst[] = "Hello, World!";
    
    checkerror_strcpy(src, dst);
    printf("Copied string: %s\n", dst);
    

    return 0;
}

