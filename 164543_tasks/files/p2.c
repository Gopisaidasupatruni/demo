#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 100

void findNreplace(char*, char*, char*, int);

int main() {
    FILE *fp;
    char str1[LEN];
    char str2[LEN];

    /* Open the file for reading */
    fp = fopen("file.txt", "r");
    if (fp == NULL) {
        printf("Error opening file for reading\n");
        return 1;
    }

    /* Get the size of the file */
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    rewind(fp);

    /* Allocate memory to store the entire file content */
    char *file_content = (char *)malloc((file_size + 1) * sizeof(char));
    if (file_content == NULL) {
        printf("Memory allocation error\n");
        fclose(fp);
        return 1;
    }

    /* Read the entire file into memory */
    fread(file_content, sizeof(char), file_size, fp);
    file_content[file_size] = '\0';
    fclose(fp);

    /* Get the strings from the user */
    printf("Enter the actual string: ");
    scanf(" %[^\n]", str1);
    printf("Enter the replacing string: ");
    scanf(" %[^\n]", str2);

    /* Replace the string in file content */
    findNreplace(file_content, str1, str2, file_size);

    /* Open the file for writing */
    fp = fopen("file.txt", "w");
    if (fp == NULL) {
        printf("Error opening file for writing\n");
        free(file_content);
        return 1;
    }

    /* Write the modified content back to the file */
    fputs(file_content, fp);

    fclose(fp);
    free(file_content);  // Free the allocated memory

    printf("Data replaced successfully.\n");

    return 0;
}

/* Function to find and replace str1 with str2 in file_content */
void findNreplace(char *file_content, char *str1, char *str2, int file_size) {
    int len1 = strlen(str1);  // Length of the original string
    int len2 = strlen(str2);  // Length of the new string

    /* Allocate memory for the new file content, assuming worst case scenario where str2 is longer */
    char *new_file_content = (char *)malloc(file_size + (len2 - len1) * 10 + 1);
    if (new_file_content == NULL) {
        printf("Memory allocation error\n");
        return;
    }

    int temp_pos = 0;
    char *pos = file_content;
    char *next_match;

    /* Loop through all occurrences of str1 in the file content */
    while ((next_match = strstr(pos, str1)) != NULL) {
        /* Copy the content up to the matched string */
        strncpy(new_file_content + temp_pos, pos, next_match - pos);
        temp_pos += next_match - pos;

        /* Copy the replacement string */
        strcpy(new_file_content + temp_pos, str2);
        temp_pos += len2;

        /* Move the position to just after the replaced string */
        pos = next_match + len1;
    }

    /* Copy any remaining content after the last match */
    strcpy(new_file_content + temp_pos, pos);

    /* Copy the result back into the original buffer */
    strcpy(file_content, new_file_content);

    /* Free the temporary buffer */
    free(new_file_content);
}

