/* Multi-Process Chat Application with Shared Memory and Sockets */
/* REQUIRED HEADER FILES */
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>     /* For socket programming */
#include <sys/un.h>         /* For Unix domain sockets */
#include <sys/ipc.h>        /* For interprocess communication (IPC) keys */
#include <sys/shm.h>        /* For shared memory */
#include <sys/sem.h>        /* For semaphore operations */
#include <string.h>         /* For string manipulation */
#include <unistd.h>         /* For POSIX API (e.g., close, fork) */
#include <sys/msg.h>        /* For message queue operations */
#include <signal.h>

/* Define the message structure */
struct message {
    long mtype;
    char text[100];
};

/* MACRO DEFINITIONS */
#define SHM_SIZE 1024    /* Shared memory size */
#define MSG_KEY 1234
#define MAX_MSG_LEN 128  /* Maximum message length */
#define SOCKET_PATH "/tmp/chat_socket"
#define MAX_MESSAGES 100
#define MAX_SENDER_ID_LEN 32

typedef struct {
    int sender_id;
    char message[MAX_MSG_LEN];
} ChatMessage;

typedef struct {
    ChatMessage messages[MAX_MESSAGES];
    int message_count; // Keeps track of the number of messages
} ChatHistory;

/* Semaphore operations */
struct sembuf sem_lock = {0, -1, 0};
struct sembuf sem_unlock = {0, 1, 0};

char confirmation[MAX_MSG_LEN];
int server_fd, client_fd, shm_id, sem_id;
int icount = 0;
ChatHistory *shared_chat;

/* handle_sigint: To indicate all clients that server has terminated */
void handle_sigint(int sig) {
    strcpy(confirmation, "1");
    write(client_fd, confirmation, strlen(confirmation));
    exit(0);
}

void display_chat_history(ChatHistory *shared_chat) {
    printf("Chat History:\n");
    for (int i = 0; i < shared_chat->message_count; ++i) {
        printf("Client %d: %s\n", shared_chat->messages[i].sender_id, shared_chat->messages[i].message);
    }
}

void add_to_chat_history(ChatHistory *shared_chat, const char *message, int sender_id) {
    if (shared_chat->message_count < MAX_MESSAGES) {
        ChatMessage *new_msg = &shared_chat->messages[shared_chat->message_count++];
        new_msg->sender_id = sender_id;
        strncpy(new_msg->message, message, MAX_MSG_LEN - 1);
        new_msg->message[MAX_MSG_LEN - 1] = '\0'; // Ensure null termination
    } else {
        printf("Chat history is full. Cannot save more messages.\n");
    }
}

/* MAIN PROGRAM */
/* main : To store input from client into message queue before attaching into shared memory and sending new messages to client */
int main() {
    struct sockaddr_un server_addr, client_addr;
    socklen_t client_len;

    if (signal(SIGINT, handle_sigint) == SIG_ERR) {
        perror("unable to catch SIGINT");
        return 1;
    }

    /* Creates Unix Domain Socket */
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    /* Configuring server address */
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);
    unlink(SOCKET_PATH);

    /* Bind socket */
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for clients\n");

    /* Listen for connections */
    if (listen(server_fd, 5) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    int msg_id;
    struct message msg;

    /* Access the message queue */
    msg_id = msgget(MSG_KEY, IPC_CREAT | 0666);
    if (msg_id < 0) {
        perror("msgget");
        exit(1);
    }
    msg.mtype = 1;

    /* Create shared memory */
    shm_id = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666);
    if (shm_id < 0) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    shared_chat = (ChatHistory *)shmat(shm_id, NULL, 0);
    if (shared_chat == (ChatHistory *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }
    shared_chat->message_count = 0;
    memset(shared_chat, 0, SHM_SIZE);

    /* Create semaphore */
    sem_id = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666);
    if (sem_id < 0) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    semctl(sem_id, 0, SETVAL, 1);

    while (1) {
        /* Accept client connection */
        client_len = sizeof(client_addr);
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
        if (client_fd < 0) {
            perror("accept");
            continue;
        }
        icount++;
        printf("Client %d connected \n", icount);

        /* Fork to handle client */
        if (fork() == 0) {
            close(server_fd);

            char buffer[MAX_MSG_LEN];
            while (1) {
                memset(buffer, 0, MAX_MSG_LEN);
                ssize_t bytes_read = read(client_fd, buffer, MAX_MSG_LEN);
                if (bytes_read > 0) {
                    buffer[strcspn(buffer, "\n")] = '\0'; // Null-terminate

                    if (strcmp(buffer, "chat") == 0) {
                        semop(sem_id, &sem_lock, 1); // Lock shared memory
                        display_chat_history(shared_chat);
                        semop(sem_id, &sem_unlock, 1); // Unlock shared memory
                        continue;
                    }

                    semop(sem_id, &sem_lock, 1); // Lock shared memory
                    add_to_chat_history(shared_chat, buffer, icount);
                    semop(sem_id, &sem_unlock, 1); // Unlock shared memory

                    printf("Client %d: %s\n", icount, buffer);
                } else if (bytes_read == 0) {
                    printf("Client disconnected.\n");
                    close(client_fd);
                    break;
                } else {
                    perror("read");
                }

                printf("\n");

                fgets(confirmation, MAX_MSG_LEN, stdin);
                write(client_fd, confirmation, strlen(confirmation));
            }
        }

        close(client_fd);
    }

    /* Cleanup (on server termination) */
    shmctl(shm_id, IPC_RMID, NULL);
    semctl(sem_id, 0, IPC_RMID);
    unlink(SOCKET_PATH);

    return 0;
}

