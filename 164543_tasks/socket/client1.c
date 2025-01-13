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
	char wrbuf[128];
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
	srv.sin_addr.s_addr=inet_addr("127.0.0.1");
	if(connect(sockfd,(struct sockaddr*)&srv,sizeof(srv))==0)
		printf("connection is successfull\n");
	printf("enter the data\n");
	scanf(" %s",wrbuf);
		write(sockfd,wrbuf,strlen(wrbuf)+1);
		

}
