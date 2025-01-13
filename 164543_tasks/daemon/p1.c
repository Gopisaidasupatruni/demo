#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    if (fork() == 0)  
    {
        printf("Child pid: %d\n", getpid());
	exit(1);
    }
    else 
    {
        printf("Parent pid: %d\n", getpid());
	
	sleep(1000);
    }

    return 0;
}
