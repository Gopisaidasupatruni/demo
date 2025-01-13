#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

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

int main() {
    printf("System Information:\n");
    get_cpu_info();
    get_kernel_version();
    get_boot_time();
    get_load_avg();
    get_memory_info();
    get_swap_info();
    get_cpu_times();
    get_context_switches();
    get_interrupts();
    return 0;
}

