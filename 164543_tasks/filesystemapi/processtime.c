#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/times.h>

int main() {
    struct tms start_time, end_time;
    clock_t start, end;
    long ticks_per_second = sysconf(_SC_CLK_TCK);

    
    start = times(&start_time);

    // Simulate work with sleep (Replace this section with actual work)
    sleep(2);

    
    end = times(&end_time);

    
    double wall_clock_time = (double)(end - start) / ticks_per_second;

    // Calculate user and system CPU time
    double user_cpu_time = (double)(end_time.tms_utime - start_time.tms_utime) / ticks_per_second;
    double system_cpu_time = (double)(end_time.tms_stime - start_time.tms_stime) / ticks_per_second;

    // Display the results
    printf("Wall Clock Time: %.2f seconds\n", wall_clock_time);
    printf("User CPU Time: %.2f seconds\n", user_cpu_time);
    printf("System CPU Time: %.2f seconds\n", system_cpu_time);

    return 0;
}

