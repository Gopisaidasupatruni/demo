#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>
#include<errno.h>
#define SOCKET_PATH "/tmp/chat_socket"
#define MAX_MSG_LEN 128

int main() {
	int client_fd;
	struct sockaddr_un server_addr;

	/* Create Unix Domain Socket */
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
	char confirm[MAX_MSG_LEN];
	while (1) {
		memset(buffer, 0, MAX_MSG_LEN);
		printf("Enter Message: ");
		fgets(buffer, MAX_MSG_LEN, stdin);

		ssize_t bytes_written=write(client_fd, buffer, strlen(buffer));
		if (bytes_written <= 0) {
			if (errno == EPIPE) {
				printf("Server has terminated. Exiting...\n");
				break;
			} else {
				perror("write");
				break;
			}
		}

		printf("Message sent.\n");
		memset(confirm, 0, MAX_MSG_LEN);
		ssize_t bytes_read = read(client_fd, confirm, MAX_MSG_LEN);
		if(!(strcmp(confirm,"1")))
		{
			printf("server terminated\n");
			exit(1);	
		}
		if (bytes_read <= 0) {
			// Server closed connection
			printf("Server has closed the connection. Exiting...\n");
			exit(0);
			close(client_fd);
		} else {
			printf("Server response: %s\n", confirm);
		}
	}
	close(client_fd);
	return 0;
}

