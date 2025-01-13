#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
int main()
{
	int sockfd,newsfd;
	struct sockaddr_in srv,cln;
	char rdbuf[128];
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

		bzero(rdbuf,128);
		read(newsfd,rdbuf,128);
		printf("received data %s",rdbuf);
		




}
