Message queue: A message queue is a data structure that allows processes to communicate and exchange data asynchronously. It is a form of inter-process communication (IPC) that stores messages in a queue. Processes can send messages to the queue and retrieve them later, even if the sending and receiving processes are not running simultaneously.
In a message queue, each message has:

Message Type: A unique identifier (usually a long integer) that allows the receiver to selectively fetch messages.
Message Data: The actual content of the message.

Advantages: 
Asynchronous communication 
Prioritization
reliability
limitations:
complexity 


system calls:
int msgget(keyt key, int msgflg);

int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);

ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp,
                      int msgflg);
