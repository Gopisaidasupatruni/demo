#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
//int fd=open("file1.txt",O_WRONLY | O_CREAT | O_TRUNC,0644);
int fd = open("f1", O_WRONLY | O_CREAT , 0644);
	if(fd<0)
	{
		perror("open");
		exit(1);
       }
	  if (lseek(fd, 4096, SEEK_SET) == -1) {
        perror("Error seeking");
        close(fd);
        return 1;
    }
	    
    

    close(fd);
	printf("%d",fd);
}
