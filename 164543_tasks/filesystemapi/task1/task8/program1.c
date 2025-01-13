/* REQUIRED HEADER FILES */
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

/* Structure to hold file information */
typedef struct FileInfo {
    char name[256];
    off_t size; /* File size */
} FileInfo;

// Comparison function for sorting files by size
int compareFiles(const void *a, const void *b) {
    FileInfo *fileA = (FileInfo *)a;
    FileInfo *fileB = (FileInfo *)b;
    // Sorting in ascending order of size
    return (fileA->size - fileB->size);
}

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;
    FileInfo files[1024];  /* Array to store file information */
    int count = 0;

    // Open the current directory
    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return EXIT_FAILURE;
    }

    // Read all files in the directory
    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".." directories
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        // Get file information using stat
        if (stat(entry->d_name, &fileStat) == -1) {
            perror("stat");
            continue;
        }

        // Store file name and size in the FileInfo struct
        strncpy(files[count].name, entry->d_name, sizeof(files[count].name));
        files[count].size = fileStat.st_size;
        count++;
    }

    // Close the directory
    closedir(dir);

    // Sort the files by size
    qsort(files, count, sizeof(FileInfo), compareFiles);

    // Print the sorted files and their sizes
    for (int i = 0; i < count; i++) {
        printf("%-20s %ld bytes\n", files[i].name, files[i].size);
    }

    return EXIT_SUCCESS;
}

