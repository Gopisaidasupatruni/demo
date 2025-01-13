/* Task5:5. Test and comment 

 

This piece of code is interesting because running it differently, we get very different results. In the following, bold letters signify keyboard inputs, while plain characters are the output. The file in1 is a plain text file: 

ABCDEFGHIJK
What is the output and difference when Run as:  

              1.  $./a.out

              2.  $./a.out < in1

              3.  $./a.out < in1 > out1
	      */
/*
 * Author: Gopisai
 * Date:10/11/2024
 */
/** REQUIRED HEADER FILES */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
/* main: To read from descriptors */
int main (void)
{
    int i, r, w;
    char msg[12];
    char buf[2] = {0, 0};
   /*Loop through the first three file descriptors: 0 (stdin), 1 (stdout), 2 (stderr)*/
    for (i = 0; i < 3; i ++) {
	    /* Attempt to read 1 byte from the current file descriptor (i)*/
      if ((r = read(i,buf,1))<0) {
         sprintf(msg,"read  f%d:%s",i,buf);   
         perror(msg);
      }
      /*Attempt to write 1 byte (from buf) to the current file descriptor (i) */
      if ((w = write(i,buf,1))<0) {
         sprintf(msg,"write f%d:%s",i,buf);
         perror(msg);
      }
      fprintf(stderr,"%d, r = %d, w = %d, char = %d\n",i,r,w,(int)(buf[0]));
    }

    return 0;
}
