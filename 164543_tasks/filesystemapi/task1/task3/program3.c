/* This program displays the contents of a directory, specifying the type for each of its files. The name for the directory should be an input parameter. */
#include <stdio.h>
#include <sys/types.h> /* for types used in system calls (like 'stat')*/
#include <sys/stat.h> /*for 'stat' structure to retrieve file status*/
#include <stdlib.h>
#include <dirent.h>/*for directory operations*/
#include <string.h>
#include <unistd.h>/* for system calls like lstat */

int main(int argc, char **argv) {
	/*  Declaring a stat structure 'v' to store file details */
    struct stat v;
    /*Declaring a pointer 'p' to a struct dirent for entries of directory */
    struct dirent *p;
    /* Declaring a pointer 'dp' to a DIR structure (used for handling directories*/
    DIR *dp;
    char path[500];  
    if (argc != 2) {
        printf("Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    dp = opendir(argv[1]);
    if (dp == NULL) {
        perror("opendir");
        exit(1);
    }

    while ((p = readdir(dp)) != NULL) {
        /*snprintf() ensures that the path does not overflow the path array.*/
        snprintf(path, sizeof(path), "%s/%s", argv[1], p->d_name);
        /*Get the status (info) about the file */
        if (lstat(path, &v) < 0) {
            perror("lstat");
            continue; 
        }

        printf("%s: ", p->d_name);
	/*  Check if it is a regular file */
        if (S_ISREG(v.st_mode))
            printf("Regular file\n");
	/*  Check if it is a directory */
        else if (S_ISDIR(v.st_mode))
            printf("Directory\n");
	/*  Check if it is a symbolic link */
        else if (S_ISLNK(v.st_mode))
            printf("Symbolic link\n");
	/*  Check if it is a character device*/
        else if (S_ISCHR(v.st_mode))
            printf("Character device\n");
	/*  Check if it is a block device file */
        else if (S_ISBLK(v.st_mode))
            printf("Block device\n");
	/*  Check if it is a named pipe */
        else if (S_ISFIFO(v.st_mode))
            printf("FIFO (named pipe)\n");
	/*  Check if it is a socket */
        else if (S_ISSOCK(v.st_mode))
            printf("Socket\n");
        else
            printf("Unknown\n");
    }

    closedir(dp);
    return 0;
}

