/** MESSAGE QUEUE */
#include<stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSG_KEY 1234


/* Define the message structure */
struct message {
    long mtype;
    char text[100];
};
int main()
{
int msg_id;
    struct message msg;

    // Access the message queue
    msg_id = msgget(MSG_KEY,IPC_CREAT | 0666);
    if (msg_id < 0) {
        perror("msgget");
        exit(1);
    
    }
    msg.mtype = 1;
    printf("Enter a message: ");
    fgets(msg.text, 100, stdin);
 if (msgsnd(msg_id, &msg, sizeof(msg.text),0) < 0) {
        perror("msgsnd");
        exit(1);
    }

    printf("Message sent: %s\n", msg.text);
    return 0;

}

