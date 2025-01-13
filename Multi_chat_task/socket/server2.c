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
#include<signal.h>
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

/* Semaphore operations */
struct sembuf sem_lock = {0, -1, 0};
struct sembuf sem_unlock = {0, 1, 0};
char confirmation[MAX_MSG_LEN];
int server_fd, client_fd, shm_id, sem_id;
void handle_sigint(int sig)
{
	strcpy(confirmation,"1");
	write(client_fd, confirmation, strlen(confirmation));
	exit(0);
}
int icount=0;
int main() {

	struct sockaddr_un server_addr, client_addr;
	char *shared_mem;

	socklen_t client_len;
	if(signal(SIGINT, handle_sigint)==SIG_ERR){
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

	//printf("Server listening on %s\n", SOCKET_PATH);
	int msg_id;
	struct message msg;

	/* Access the message queue */
	msg_id = msgget(MSG_KEY,IPC_CREAT | 0666);
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

	shared_mem = (char *)shmat(shm_id, NULL, 0);
	if (shared_mem == (char *)-1) {
		perror("shmat");
		exit(EXIT_FAILURE);
	}

	memset(shared_mem, 0, SHM_SIZE);

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
		printf("Client %d connected \n.",icount);

		/* Fork to handle client */
		if (fork() == 0) {
			close(server_fd);

			char buffer[MAX_MSG_LEN];
			while (1) {
				memset(buffer, 0, MAX_MSG_LEN);
				ssize_t bytes_read = read(client_fd, buffer, MAX_MSG_LEN);
				if (bytes_read <= 0) {
					printf("Client disconnected.\n");
					close(client_fd);
					exit(0);
				}
				strcpy(msg.text,buffer);	
				if (msgsnd(msg_id, &msg, sizeof(msg.text),0) < 0) {
					perror("msgsnd");
					exit(1);
				}
				/* Synchronize access to shared memory using semaphore */
				semop(sem_id, &sem_lock, 1);
				if (msgrcv(msg_id, &msg, sizeof(msg.text), 0, 0) < 0) {
					perror("msgrcv");
					exit(1);
				}

				/* Write to shared memory */
				strncat(shared_mem, msg.text, SHM_SIZE - strlen(shared_mem) - 1);

				semop(sem_id, &sem_unlock, 1);

				printf("Message received: %s", msg.text);
			//	printf("Enter new message:\n"); 
				fgets(confirmation, MAX_MSG_LEN, stdin);
				//	snprintf(confirmation, MAX_MSG_LEN, "Message received: %.100s", msg.text);
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

