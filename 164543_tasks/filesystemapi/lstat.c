#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
int main(int argc,char**argv)
{
	struct stat v;
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
	printf("inode %ld\n size %ld\nnumber of blocks%ld\npermission %o\n",v.st_ino,v.st_size,v.st_blocks,v.st_mode);

}
