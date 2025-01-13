#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

void print_file_type(struct stat *file_stat, char *filename) {
    if (S_ISDIR(file_stat->st_mode)) {
        printf("%s/\n", filename);  // Directory
    } else if (S_ISLNK(file_stat->st_mode)) {
        printf("%s@\n", filename);  // Symbolic link
    } else if (file_stat->st_mode & S_IXUSR) {
        printf("%s*\n", filename);  // Executable file
    } else {
        printf("%s\n", filename);   // Regular file
    }
}

void ls_F() {
    struct dirent *entry;
    struct stat file_stat;

    DIR *dir = opendir(".");
    if (!dir) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (stat(entry->d_name, &file_stat) == 0) {
            print_file_type(&file_stat, entry->d_name);
        } else {
            perror("stat");
        }
    }
    closedir(dir);
}

int main() {
    ls_F();
    return 0;
}

