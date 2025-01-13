/* tt.c */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>
#include <unistd.h>

// Structure to store different types of time measurements
typedef struct {
  clock_t        clock_val;      // Clock time from the clock() function
  time_t         time_val;       // Wall clock time from time()
  struct timeval gettime_val;    // High-precision wall clock time from gettimeofday()
  struct tms     times_val;      // User and system CPU time from times()
} all_times;

// Function to fill the provided `all_times` structure with current time values
void get_time(all_times * t)
{
  t->clock_val = clock();                         // Clock time since program start
  t->time_val = time(NULL);                       // Wall clock time in seconds since epoch
  gettimeofday(&(t->gettime_val), NULL);          // Wall clock time with microseconds precision
  times(&(t->times_val));                         // User and system CPU time for the process
}

// Function to print the duration between two `all_times` structures (t1 and t2)
void print_duration(all_times * t1, all_times * t2)
{
  float elapsed;                                  // Variable to store elapsed time
  long clktck, nticks; 

  // Calculate and print the elapsed CPU time from clock() in seconds
  nticks = t2->clock_val - t1->clock_val;
  elapsed = (float)nticks / CLOCKS_PER_SEC; 
  fprintf(stderr, "clock: %f sec\n", elapsed);

  // Calculate and print the elapsed wall clock time in seconds from time()
  nticks = t2->time_val - t1->time_val;
  fprintf(stderr, "time: %d sec\n", nticks);

  // Calculate and print the elapsed time in seconds with microsecond precision using gettimeofday()
  elapsed = t2->gettime_val.tv_sec - t1->gettime_val.tv_sec;
  elapsed += (t2->gettime_val.tv_usec - t1->gettime_val.tv_usec) / 1e6;
  fprintf(stderr, "gettimeofday: %f sec\n", elapsed);

  // Get the number of clock ticks per second (depends on system)
  clktck = sysconf(_SC_CLK_TCK);

  // Calculate and print the user CPU time (in seconds)
  nticks = t2->times_val.tms_utime - t1->times_val.tms_utime;
  elapsed = (float)nticks / clktck;  
  fprintf(stderr, "times: %f sec user time\n", elapsed);

  // Calculate and print the system CPU time (in seconds)
  nticks = t2->times_val.tms_stime - t1->times_val.tms_stime;
  elapsed = (float)nticks / clktck;  
  fprintf(stderr, "times: %f sec system time\n", elapsed);
}

// Function that copies data from standard input to standard output
long simplecat()
{
  char c;
  int i;
  long cnt = 0;

  // Read each character from stdin and write it to stdout
  i = fread(&c, 1, 1, stdin);
  while(i > 0) {
    fwrite(&c, 1, 1, stdout);
    i = fread(&c, 1, 1, stdin);
    cnt++;                    // Count the total number of bytes processed
  }

  return cnt;
}

int main(void)
{
  int totalbytes;
  all_times a1, a2;           // Structures to store time data before and after `simplecat`

  get_time(&a1);              // Record start times

  totalbytes = simplecat();   // Perform the copy operation

  get_time(&a2);              // Record end times
  print_duration(&a1, &a2);   // Print the elapsed times for the operation

  // Print the total bytes processed in MiB (1 MiB = 1,000,000 bytes)
  fprintf(stderr, "total of %f MiB\n", totalbytes / 1e6);

  return 0;
}

