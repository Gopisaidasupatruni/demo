#include<stdio.h>
#include<errno.h>

int main()
{
  int i;
  FILE *f;

  f = fopen("p8.c", "r");
  if (f == NULL) {
    //printf("f = null.  errno = %d\n", errno);
    perror("f");
  }
}
