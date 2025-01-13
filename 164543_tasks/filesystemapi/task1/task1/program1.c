/* This program is to create a file with a 4K bytes free space. Such files are called files with holes.*/

/* REQUIRED HEADER FILES */
#include<stdio.h>
#include<fcntl.h>/* O_WRONLY O_CREAT*/
#include<stdlib.h>
#include<unistd.h>/* POSIX standard library read() write() lseek() */
/* main: To create a file with 4k bytes */
int main()
{
	//int fd=open("file1.txt",O_WRONLY | O_CREAT | O_TRUNC,0644);
	/* Open or create the file with read/write permissions */
	int fd = open("file1.c", O_WRONLY | O_CREAT , 0644);
	if(fd<0)
	{
		perror("open");
		exit(1);
	}
	/* write content */
	if(write(fd, "Hello",5)!=5)
	{
		perror("error");
		close(fd);
	}
	/* Move the file pointer 4096 bytes forward to create a 4K hole */
	if (lseek(fd, 5, SEEK_CUR) == -1) {
		perror("Error seeking");
		close(fd);
		return 1;
	}
	/* Write a 5 byte to allocate the space (the file now has a hole) */
	if (write(fd, "world", 5) != 5) {
		perror("Error writing to file");
		close(fd);
		exit(1);
	}
	if (lseek(fd, 4081, SEEK_CUR) == -1) {
		perror("Error seeking");
		close(fd);
		return 1;
	}
	if (write(fd, "", 1) != 1) {
		perror("Error writing to file");
		close(fd);
		exit(1);
	}


	close(fd);
	printf("%d",fd);
}
/* End main() */
