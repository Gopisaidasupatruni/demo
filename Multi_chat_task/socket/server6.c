#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

#define SOCKET_PATH "/tmp/chat_socket"
#define MAX_MSG_LEN 128
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

char confirmation[MAX_MSG_LEN];
char buffer_send[MAX_MSG_LEN];
int server_fd, client_id=0;;
ChatHistory shared_chat;
pthread_mutex_t chat_lock = PTHREAD_MUTEX_INITIALIZER;

/* handle_sigint: To indicate all clients that server has terminated */
void handle_sigint(int sig) {
    printf("Server shutting down.\n");
    unlink(SOCKET_PATH);
    exit(0);
}

void display_chat_history(ChatHistory *shared_chat,int client_fd) {
    printf("Chat History:\n");
    for (int i = 0; i < shared_chat->message_count; ++i) {
        printf("Client  %s\n", shared_chat->messages[i].message);
        //printf("Client %d: %s\n", shared_chat->messages[i].sender_id, shared_chat->messages[i].message);
    }
    int buffer_length = 0;

    // Prepare chat history as a single string to send to the client
    buffer_length += snprintf(buffer_send + buffer_length, sizeof(buffer_send) - buffer_length, "Chat History:\n");
    for (int i = 0; i < shared_chat->message_count; ++i) {
        buffer_length += snprintf(
            buffer_send + buffer_length,
            sizeof(buffer_send) - buffer_length,
            "Client %s\n", 
            shared_chat->messages[i].message
        );

        // Ensure the buffer doesn't overflow
        if (buffer_length >= sizeof(buffer_send) - 1) {
            break;
        }
    }
        write(client_fd, buffer_send, strlen(buffer_send));

}

void add_to_chat_history(ChatHistory *shared_chat, const char *message, int sender_id) {
    pthread_mutex_lock(&chat_lock);
    if (shared_chat->message_count < MAX_MESSAGES) {
        ChatMessage *new_msg = &shared_chat->messages[shared_chat->message_count++];
        new_msg->sender_id = sender_id;
        strncpy(new_msg->message, message, MAX_MSG_LEN - 1);
        new_msg->message[MAX_MSG_LEN - 1] = '\0'; // Ensure null termination
    } else {
        printf("Chat history is full. Cannot save more messages.\n");
    }
    pthread_mutex_unlock(&chat_lock);
}

/* Thread function to handle client communication */
void *client_handler(void *arg) {
    int client_fd = *(int *)arg;
    free(arg);
    char buffer[MAX_MSG_LEN];


    //printf("Client connected. Thread ID: %d\n", client_id);
    while (1) {
        memset(buffer, 0, MAX_MSG_LEN);
        ssize_t bytes_read = read(client_fd, buffer, MAX_MSG_LEN);

        if (bytes_read > 0) {
            buffer[strcspn(buffer, "\n")] = '\0'; // Null-terminate

            if (strcmp(buffer, "chat") == 0) {
                pthread_mutex_lock(&chat_lock);
                display_chat_history(&shared_chat,client_fd);
                pthread_mutex_unlock(&chat_lock);
                continue;
            }

            add_to_chat_history(&shared_chat, buffer, client_id);

            printf("Client %s\n", buffer);
        } else if (bytes_read == 0) {
            printf("Client %d disconnected.\n", client_id);
            close(client_fd);
            break;
        } else {
            perror("read");
        }

        // Sending confirmation back to the client
 //       snprintf(confirmation, MAX_MSG_LEN, "Message received: %s", buffer);
 	fgets(confirmation,sizeof(confirmation),stdin);
        write(client_fd, confirmation, strlen(confirmation));
    }

    close(client_fd);
    return NULL;
}

int main() {
    struct sockaddr_un server_addr, client_addr;
    socklen_t client_len;

    if (signal(SIGINT, handle_sigint) == SIG_ERR) {
        perror("unable to catch SIGINT");
        return 1;
    }

    /* Create Unix Domain Socket */
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    /* Configure server address */
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);
    unlink(SOCKET_PATH);

    /* Bind socket */
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for clients...\n");

    /* Listen for connections */
    if (listen(server_fd, 5) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    memset(&shared_chat, 0, sizeof(shared_chat));

    while (1) {
        /* Accept client connection */
        client_len = sizeof(client_addr);
        int *client_fd_ptr = malloc(sizeof(int));
        *client_fd_ptr = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
        if (*client_fd_ptr < 0) {
            perror("accept");
            free(client_fd_ptr);
            continue;
        }
         client_id++;
        /* Create a thread to handle the client */
        pthread_t thread;
        if (pthread_create(&thread, NULL, client_handler, client_fd_ptr) != 0) {
            perror("pthread_create");
            close(*client_fd_ptr);
            free(client_fd_ptr);
            continue;
        }

        pthread_detach(thread); // Automatically clean up thread resources
    }

    /* Cleanup */
    unlink(SOCKET_PATH);
    return 0;
}

