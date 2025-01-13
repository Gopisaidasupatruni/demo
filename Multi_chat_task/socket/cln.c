#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

#define SOCKET_PATH "/tmp/chat_socket" // Path for the Unix Domain Socket
#define MAX_MSG_LEN 128               // Maximum message length

int client_fd;                         // File descriptor for the client socket
char confirm[MAX_MSG_LEN];             // Buffer to store messages from the server

/**
 * print_message: Thread function to listen for server messages.
 * Continuously reads and prints messages from the server.
 */
void *print_message(void *thread_id) {
    while (1) {
        memset(confirm, 0, MAX_MSG_LEN);

        // Read message from the server
        ssize_t bytes_read = read(client_fd, confirm, MAX_MSG_LEN);

        if (bytes_read <= 0) {
            // Server closed the connection or an error occurred
            if (bytes_read == 0) {
                printf("Server has closed the connection. Exiting...\n");
            } else {
                perror("read");
            }
            exit(EXIT_FAILURE);
        }

        // Check for server termination signal
        if (strcmp(confirm, "1") == 0) {
            printf("Server terminated. Exiting...\n");
            exit(EXIT_FAILURE);
        }

        // Print the message from the server
        printf("Server: %s\n", confirm);
    }

    return NULL;
}

/**
 * main: Entry point of the client program.
 * Establishes connection with the server, starts a thread for receiving messages,
 * and allows the user to send messages to the server.
 */
int main() {
    struct sockaddr_un server_addr; // Server address structure
    pthread_t thread;               // Thread for receiving messages

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
    close(client_fd);               // Close the client socket
    pthread_cancel(thread);         // Terminate the thread
    pthread_join(thread, NULL);     // Wait for the thread to finish
    return 0;
}

