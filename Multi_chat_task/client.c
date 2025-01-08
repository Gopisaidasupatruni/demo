#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/chat_socket"
#define MAX_MSG_LEN 128

int main() {
    int client_fd;
    struct sockaddr_un server_addr;

    // Create Unix Domain Socket
    client_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (client_fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    // Connect to server
    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server. Type messages to send:\n");

    // Chat loop
    char buffer[MAX_MSG_LEN];
    while (1) {
        memset(buffer, 0, MAX_MSG_LEN);
        printf("You: ");
        fgets(buffer, MAX_MSG_LEN, stdin);

        if (write(client_fd, buffer, strlen(buffer)) < 0) {
            perror("write");
            break;
        }

        printf("Message sent.\n");
    }

    close(client_fd);
    return 0;
}

