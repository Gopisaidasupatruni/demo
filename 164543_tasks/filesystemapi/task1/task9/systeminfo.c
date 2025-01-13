/* This program is to write a C program SystemInfo.c that will read the /proc file system and print out  the following (with an appropriate message in each case): 

1. The number of CPUs in your machine and their clock speed, number of cores. 
2. The version of Linux kernel running on your system 
3. The time in day:hr:min:sec when the system was last booted 
4. The average load on the system in the last 15 minutes 
5. The total usable and currently free memory in the system 
6. The total swap space and the currently used swap space in the system 
7. The swap partitions and their sizes 
8. The time the CPU spent (over all processes) in the user mode and kernel mode 
9. The number of context switches made by the system so far 
10. The number of interrupts handled by the system so far 
*/
/* REQUIRED HEADER FILES */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
/* cpu information */
void get_cpu_info() {
    FILE *fp = fopen("/proc/cpuinfo", "r");
    if (!fp) {
        perror("Failed to open /proc/cpuinfo");
        return;
    }
    int cpu_count = 0;
    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, "processor")) cpu_count++;
        if (strstr(line, "cpu MHz")) printf("%s", line);
    }
    fclose(fp);
    printf("Number of CPUs: %d\n", cpu_count);
}
/* kernel version */
void get_kernel_version() {
    FILE *fp = fopen("/proc/version", "r");
    if (!fp) {
        perror("Failed to open /proc/version");
        return;
    }
    char version[256];
    fgets(version, sizeof(version), fp);
    printf("Kernel Version: %s", version);
    fclose(fp);
    
}
/*get_boot_time: when the system was last booted */
void get_boot_time() {
    FILE *fp = fopen("/proc/uptime", "r");
    if (!fp) {
        perror("Failed to open /proc/uptime");
        return;
    }
    double uptime_seconds;
    fscanf(fp, "%lf", &uptime_seconds);
    fclose(fp);

    time_t boot_time = time(NULL) - (time_t)uptime_seconds;
    struct tm *bt = localtime(&boot_time);
    printf("System booted on: %02d:%02d:%02d:%02d\n", bt->tm_mday, bt->tm_hour, bt->tm_min, bt->tm_sec);
}
/*get_load_avg:The average load on the system in the last 15 minutes */
void get_load_avg() {
    FILE *fp = fopen("/proc/loadavg", "r");
    if (!fp) {
        perror("Failed to open /proc/loadavg");
        return;
    }
    double load_15;
    fscanf(fp, "%*f %*f %lf", &load_15);
    printf("Average load in the last 15 minutes: %.2f\n", load_15);
    fclose(fp);
}
/* get_memory_info : memory information */
void get_memory_info() {
    FILE *fp = fopen("/proc/meminfo", "r");
    if (!fp) {
        perror("Failed to open /proc/meminfo");
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, "MemTotal:") || strstr(line, "MemFree:")) {
            printf("%s", line);
        }
    }
    fclose(fp);
}
/* get_swap_info : get swap information */
void get_swap_info() {
    FILE *fp = fopen("/proc/meminfo", "r");
    if (!fp) {
        perror("Failed to open /proc/meminfo");
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, "SwapTotal:") || strstr(line, "SwapFree:")) {
            printf("%s", line);
        }
    }
    fclose(fp);
}
/* get_cpu_times: time cpu spent*/
void get_cpu_times() {
    FILE *fp = fopen("/proc/stat", "r");
    if (!fp) {
        perror("Failed to open /proc/stat");
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, "cpu ")) {
            printf("CPU times (user, system): %s", line);
            break;
        }
    }
    fclose(fp);
}

void get_context_switches() {
    FILE *fp = fopen("/proc/stat", "r");
    if (!fp) {
        perror("Failed to open /proc/stat");
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, "ctxt")) {
            printf("Context switches: %s", line);
            break;
        }
    }
    fclose(fp);
}

void get_interrupts() {
    FILE *fp = fopen("/proc/stat", "r");
    if (!fp) {
        perror("Failed to open /proc/stat");
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, "intr")) {
            printf("Interrupts handled: %s", line);
            break;
        }
    }
    fclose(fp);
}

/* main : To know systeminfo */
int main() {
    printf("System Information:\n");
    get_cpu_info();
    printf("\n");
    get_kernel_version();
    printf("\n");
    get_boot_time();
    printf("\n");
    get_load_avg();
    printf("\n");
    get_memory_info();
    printf("\n");
    get_swap_info();
    printf("\n");
    get_cpu_times();
    printf("\n");
    get_context_switches();
    printf("\n");
    get_interrupts();
    printf("\n");
    return 0;
}

