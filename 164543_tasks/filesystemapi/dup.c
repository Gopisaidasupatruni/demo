#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
int fd1,fd2;
fd1=open("temp",O_WRONLY|O_CREAT|O_TRUNC,0644);
if(fd1<0)
{
	perror("open");
	exit(1);
}
fd2=dup(fd1);
printf("%d %d",fd1,fd2);
write(fd1,"hello",5);
write(fd2,"chennai",7);
}
