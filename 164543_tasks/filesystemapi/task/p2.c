#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#define LOG_FILE "/home/gopisai/linux_fun/task1/logfile"
void write_to_fill_log()
{
  char *username;
  long t;
  FILE *f;
 
  username = getenv("USER");
  t = time(0);
  
  f = fopen(LOG_FILE, "a");
      if (f == NULL) {
        perror("Error opening log file");
        return;
    }
  /* error check */
  sleep(1);
  fprintf(f,"%s %ld in file2\n", username, t);
  fclose(f);
}
int main()
{
      int n=10;
      while(n!=0){
	write_to_fill_log();
  n--;
      }
}
