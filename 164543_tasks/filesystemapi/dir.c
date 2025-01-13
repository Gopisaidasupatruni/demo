#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<dirent.h>
#include<time.h>
#include<string.h>
#include<sys/types.h>
int main(int argc,char *argv[])
{
	struct stat v;
       struct dirent*p;
	DIR*dp;
        char path[20];	
	int i;
	dp=opendir(argv[1]);
	if(dp==0)
	{
		perror("opendir");
		exit(1);
       }
	while(p=readdir(dp))
		printf("%s \n",p->d_name);


}
