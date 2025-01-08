A semaphore is a synchronization primitive used to control access to a shared resource by multiple processes or threads. It is especially useful in preventing race conditions and ensuring safe access to critical sections in concurrent programming.
Types of Semaphores
Binary Semaphore:
Acts like a lock with two states:

0 (locked): Resource is unavailable.
1 (unlocked): Resource is available.
Counting Semaphore:
Can have a value greater than 1, representing multiple instances of a resource.

Semaphore Operations
P (Wait/Decrement/Lock):

Checks if the semaphore value is greater than 0.
Decrements the value by 1.
If the value is 0, the process blocks until the resource becomes available.
V (Signal/Increment/Unlock):

Increments the semaphore value by 1.
If processes are waiting, it unblocks one of them
semget()

Creates or accesses a semaphore set.
Returns a semaphore ID.

int semget(key_t key, int nsems, int semflg);
semctl()

int semctl(int semid, int semnum, int cmd, ...);
semop()

int semop(int semid, struct sembuf *sops, size_t nsops);
