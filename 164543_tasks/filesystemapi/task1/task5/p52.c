/** Required header files */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

/* 2D array */
char msg[6][15] = {"read  stdin",
                   "write stdin",
                   "read  stdout",
                   "write stdout",
                   "read  stderr",
                   "write stderr"};

int main (void)
{
    int i, r, w;
    char buf[2] = {0, 0};

    for (i = 0; i < 3; i ++) {
      if ((r = read(i,buf,1))<0) 
         perror(msg[i*2]);
      
      if ((w = write(i,buf,1))<0) 
         perror(msg[i*2+1]);

      fprintf(stderr,"%d, r = %d, w = %d, char = %d\n",i,r,w,(int)(buf[0]));
    }

    return 0;
}
