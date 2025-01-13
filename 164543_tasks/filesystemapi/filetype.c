#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
int main(int argc,char**argv)
{
	struct stat v;
	int mode;

	if(argc!=2)
	{
		printf("usage exe file \n");
		return 1;
	}
	if(lstat(argv[1],&v)<0)
	{
		perror("stat");
		exit(1);
	}
	printf("mode %o\n",v.st_mode);
	if(S_ISREG(v.st_mode))
		printf("regular file\n");
	else if(S_ISDIR(v.st_mode))
		printf("directory file\n");
	else if(S_ISLNK(v.st_mode))
                printf("link file\n");
	else if(S_ISCHR(v.st_mode))
                printf("character file\n");
	else if(S_ISBLK(v.st_mode))
                printf("block file\n");
	else if(S_ISFIFO(v.st_mode))
                printf("pipe file\n");
	else
		printf("error\n");

}
