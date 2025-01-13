#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
int main()
{
//int fd=open("file1.txt",O_WRONLY | O_CREAT | O_TRUNC,0644);
int fd = open("f1", O_WRONLY | O_CREAT | O_EXCL, 0644);
	if(fd<0)
	{
		perror("open");
		exit(1);
       }
	printf("%d",fd);
}
