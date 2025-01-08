Shared memory is an inter-process communication (IPC) mechanism in Linux that allows multiple processes to access the same region of memory. It is one of the fastest IPC mechanism

shmget(): Allocates a shared memory segment.
shmat(): Attaches the shared memory segment to the process's address space.
shmdt(): Detaches the shared memory segment.
shmctl(): Performs control operations on shared memory.

int shmget(keyt key,size,int shmflg);

void * shmat(int shmid,const void* shmaddr , int shmflg);


