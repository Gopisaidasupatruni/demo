#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

struct file_info {
    char name[256];
    off_t size;
};

int compare(const void *a, const void *b) {
    return strcmp(((struct file_info *)a)->name, ((struct file_info *)b)->name);
}

void list_files() {
    struct dirent *entry;
    struct stat file_stat;
    struct file_info files[1000];
    int count = 0;

    DIR *dir = opendir(".");
    if (!dir) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (stat(entry->d_name, &file_stat) == 0) {
            strncpy(files[count].name, entry->d_name, 255);
            files[count].size = file_stat.st_size;
            count++;
        }
    }
    closedir(dir);

    qsort(files, count, sizeof(struct file_info), compare);

    printf("Filename\tSize\n");
    for (int i = 0; i < count; i++) {
        printf("%s\t%ld bytes\n", files[i].name, files[i].size);
    }
}

int main() {
    list_files();
    return 0;
}

