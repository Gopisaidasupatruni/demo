#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

#define SOCKET_PATH "/tmp/chat_socket"
#define MAX_MSG_LEN 128
#define MAX_MESSAGES 100
#define MAX_SENDER_ID_LEN 32

typedef struct {
    char sender_id[MAX_SENDER_ID_LEN];
    char message[MAX_MSG_LEN];
} ChatMessage;

typedef struct {
    ChatMessage messages[MAX_MESSAGES];
    int message_count;  // Keeps track of the number of messages
} ChatHistory;

ChatHistory *shared_chat;
int shm_id;

// Display chat history from shared memory
void display_chat_history(const ChatHistory *chat) {
    printf("\nChat History:\n");
    for (int i = 0; i < chat->message_count; i++) {
        printf("[%s]: %s\n", chat->messages[i].sender_id, chat->messages[i].message);
    }
}
int client_fd;
char confirm[MAX_MSG_LEN];

/*print_message: Thread function to listen for server messages */
void *print_message(void *thread_id) {
    while (1) {
        memset(confirm, 0, MAX_MSG_LEN);

        // Read message from server
        ssize_t bytes_read = read(client_fd, confirm, MAX_MSG_LEN);

        if (bytes_read <= 0) {
            // Server closed connection or error occurred
            if (bytes_read == 0) {
                printf("Server has closed the connection. Exiting...\n");
            } else {
                perror("read");
            }
            exit(EXIT_FAILURE);
        }

        if (strcmp(confirm, "1") == 0) {
            printf("Server terminated. Exiting...\n");
            exit(EXIT_FAILURE);
        }

        printf("Server: %s\n", confirm);
	display_chat_history(shared_chat);
    }

    return NULL;
}

int main() {
    struct sockaddr_un server_addr;
    pthread_t thread;

    /* Create Unix Domain Socket */
    client_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (client_fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    /* Configure server address */
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    /* Connect to server */
    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server. Type messages to send:\n");

    /* Create a thread to handle incoming messages */
    if (pthread_create(&thread, NULL, print_message, NULL) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    /* Chat loop for sending messages */
    char buffer[MAX_MSG_LEN];
    while (1) {
        memset(buffer, 0, MAX_MSG_LEN);

        /* Read input from user */
        fgets(buffer, MAX_MSG_LEN, stdin);

        /* Write message to server */
        ssize_t bytes_written = write(client_fd, buffer, strlen(buffer));
        if (bytes_written <= 0) {
            /* Handle write errors */
            if (errno == EPIPE) {
                printf("Server has terminated. Exiting...\n");
            } else {
                perror("write");
            }
            break;
        }
    }

    /* Cleanup */
    close(client_fd);
    pthread_cancel(thread); /* Terminate the thread */
    pthread_join(thread, NULL); /* Wait for the thread to finish */
    return 0;
}

