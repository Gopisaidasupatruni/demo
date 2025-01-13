#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
int main()
{
  char *c;
  int fd, sz, i;

  c = (char *) calloc(100, sizeof(char));
  fd = open("in1", O_RDONLY);
  if (fd < 0) { perror("open"); exit(1); }

  sz = read(fd, c, 10);
  printf("We have opened in1, and called read(%d, c, 10).\n", fd);
  printf("It returned that %d bytes  were read.\n", sz);
  c[sz] = '\0';
  printf("Those bytes are as follows: %s\n", c);

  i = lseek(fd, 0, SEEK_CUR);
  printf("lseek(%d, 0, SEEK_CUR) returns that the current offset of the file is %d\n\n", fd, i);

  printf("now, we seek to the beginning of the file and call read(%d, c, 10)\n",
         fd);
  lseek(fd, 0, SEEK_SET);
  sz = read(fd, c, 10);
  c[sz] = '\0';
  printf("The read returns the following bytes: %s\n", c);

  printf("now, we do lseek(%d, -6, flag).  It returns %d\n",
         fd, lseek(fd, -6, SEEK_CUR));
  printf("If we do read(%d, c, 10), we get the following bytes: ", fd);

  sz = read(fd, c, 10);
  c[sz] = '\0';
  printf("%s\n", c);

  printf("Finally, we do lseek(%d, -1, flag).  This returns -1.\n", fd);
  printf("perror() tells us why: ");
  fflush(stdout);

  i = lseek(fd, -1, SEEK_SET);
  perror("l1");
  close(fd);
  return 0;
}
