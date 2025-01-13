#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

long calculate(const char *dir_path);

int main() {
    const char *current_directory = ".";
    long total_size = calculate(current_directory);
    printf("Total size of all files (excluding symlinks) in current directory and subdirectories: %ld bytes\n", total_size);
    return 0;
}

long calculate(const char *dir_path) {
    DIR *dir = opendir(dir_path);
    if (!dir) {
        perror("opendir");
        return 0;
    }

    struct dirent *entry;
    struct stat file_stat;
    long total_size = 0;

    while ((entry = readdir(dir)) != NULL) {
        // Skip the "." and ".." entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Construct the full path to the file or directory
        char path[PATH_MAX];
        snprintf(path, sizeof(path), "%s/%s", dir_path, entry->d_name);

        // Get file information
        if (lstat(path, &file_stat) == -1) {
            perror("stat");
            continue;
        }

        // Exclude symbolic links
        if (S_ISLNK(file_stat.st_mode)) {
            continue;
        }

        // If it's a regular file, add its size to the total
        if (S_ISREG(file_stat.st_mode)) {
            total_size += file_stat.st_size;
        }
        // If it's a directory, recursively calculate its size
        else if (S_ISDIR(file_stat.st_mode)) {
            total_size += calculate(path);
        }
    }

    closedir(dir);
    return total_size;
}

