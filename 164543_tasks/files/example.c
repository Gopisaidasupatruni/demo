/* This program is to replace a person town in a file with another person town which doesnt effect other information */
/* Author : Gopisai
 * Date :30/9/2024
 */ 
/* REQUIRED HEADER FILES */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
	int fp;
	fp = open("file",O_RDWR|O_CREAT,0777);
	if(fp < 0)
	{
		printf("error\n");
		exit(1);
	}
	int ch;
	/* Reads data */
	

	ch=close(fp);
}
