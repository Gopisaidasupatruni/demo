/*This program is to write another C program ProcessInfo.c that gets the following information specific to a 
process. The program takes the pid of the process as a command line argument. 
1. The command line with which the process was started 
2. The time spent by the process in running and in waiting 
3. The time spent by the process in the user mode, kernel mode 
4. The environment of the process 
5. The contents of the address space of the process 
*/
/* REQUIRED HEADER FILES */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_command_line(int pid) {
    char path[256];
    snprintf(path, sizeof(path), "/proc/%d/cmdline", pid);
    FILE *fp = fopen(path, "r");
    if (!fp) {
        perror("Failed to open cmdline");
        return;
    }
    char cmdline[256];
    fgets(cmdline, sizeof(cmdline), fp);
    printf("Command line: %s\n", cmdline);
    fclose(fp);
}

void get_process_stat(int pid) {
    char path[256];
    snprintf(path, sizeof(path), "/proc/%d/stat", pid);
    FILE *fp = fopen(path, "r");
    if (!fp) {
        perror("Failed to open stat");
        return;
    }
    int utime, stime;
    fscanf(fp, "%*d %*s %*c %*d %*d %*d %*d %*d %*d %*u %*u %*u %*u %*u %d %d", &utime, &stime);
    printf("User time: %d, System time: %d\n", utime, stime);
    fclose(fp);
}

void get_environment(int pid) {
    char path[256];
    snprintf(path, sizeof(path), "/proc/%d/environ", pid);
    FILE *fp = fopen(path, "r");
    if (!fp) {
        perror("Failed to open environ");
        return;
    }
    char env[4096];
    fread(env, 1, sizeof(env), fp);
    printf("Environment:\n%s\n", env);
    fclose(fp);
}

void get_memory_map(int pid) {
    char path[256];
    snprintf(path, sizeof(path), "/proc/%d/maps", pid);
    FILE *fp = fopen(path, "r");
    if (!fp) {
        perror("Failed to open maps");
        return;
    }
    printf("Memory Map:\n");
    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }
    fclose(fp);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pid>\n", argv[0]);
        return 1;
    }

    int pid = atoi(argv[1]);
    printf("Process Information for PID %d:\n", pid);
    get_command_line(pid);
    get_process_stat(pid);
    get_environment(pid);
    get_memory_map(pid);

    return 0;
}

