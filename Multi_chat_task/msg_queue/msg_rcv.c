#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSG_KEY 1234
#define MAX_TEXT 100

// Define the message structure
struct message {
    long mtype;
    char text[MAX_TEXT];
};

int main() {
    int msg_id;
    struct message msg;

    // Access the message queue
    msg_id = msgget(MSG_KEY, 0666);
    if (msg_id < 0) {
        perror("msgget");
        exit(1);
    }

    // Receive the message
    if (msgrcv(msg_id, &msg, sizeof(msg.text), 0, 0) < 0) {
        perror("msgrcv");
        exit(1);
    }

    printf("Received message: %s\n", msg.text);
    return 0;
}

