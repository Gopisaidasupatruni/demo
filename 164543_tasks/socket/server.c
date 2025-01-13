#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#define MAX_INPUT_SIZE 256
int main()
{
	int sockfd,newsfd,n;
	struct sockaddr_in srv,cln;
	char buffer[MAX_INPUT_SIZE];
	/* socket creation */
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)
	{
		perror("socket");
		return 0;
	}
	printf("socket created\n");
	srv.sin_family=AF_INET;
	srv.sin_port= htons(2030);
	srv.sin_addr.s_addr=inet_addr("0.0.0.0");
	if(bind(sockfd,(struct sockaddr*)&srv,sizeof(srv))==0)
		printf("binding is successfull\n");
	else
		perror("bind");
	if(listen(sockfd,1)==0)
		printf("server is listening \n");
	else
		perror("listen");

	int len=sizeof(cln);
	newsfd=accept(sockfd,(struct sockaddr*)&cln,&len);
		if(newsfd<0)
			perror("accept");
		printf("accepted new connection\n");
do{
		
        bzero(buffer, MAX_INPUT_SIZE);

        // Read message from client
        n = read(newsfd, buffer, MAX_INPUT_SIZE - 1);
        if (n < 0)
            perror("ERROR reading from socket");

        printf("Client message: %s\n", buffer);

        // Respond to client
        if (strncmp(buffer, "Bye", 3) == 0 && buffer[3] == '\n')
        {
            n = write(newsfd, "Goodbye", 7);
        }
        else
        {
            n = write(newsfd, "OK", 2);
        }

        if (n < 0)
            perror("ERROR writing to socket");

    } while (!(strncmp(buffer, "Bye", 3) == 0 && buffer[3] == '\n'));

    printf("In Server , disconnected.\n");




}
