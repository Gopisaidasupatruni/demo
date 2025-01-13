#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#define MAX_INPUT_SIZE 256
int main()
{
	int sockfd,newsfd,n;
	struct sockaddr_in srv,cln;
	char inputbuf[MAX_INPUT_SIZE];
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
		 do
      {
	/* Ask user for message to send to server */
	printf("Please enter the message to the server: ");
	bzero(inputbuf,MAX_INPUT_SIZE);
	fgets(inputbuf,MAX_INPUT_SIZE-1,stdin);
	
	/* Write to server */
	n = write(sockfd,inputbuf,strlen(inputbuf));
	if (n < 0) 
	  {
	    fprintf(stderr, "ERROR writing to socket\n");
	    exit(1);
	  }
	
	/* Read reply */
	bzero(inputbuf,MAX_INPUT_SIZE);
	n = read(sockfd,inputbuf,(MAX_INPUT_SIZE-1));
	if (n < 0) 
	  {
	    fprintf(stderr, "ERROR reading from socket\n");
	    exit(1);
	  }
	printf("Server replied: %s\n",inputbuf);

	/* Check that reply is either OK or Goodbye */
	if(! (  (inputbuf[0] == 'G' && inputbuf[1] == 'o' && inputbuf[2] == 'o' && inputbuf[3] == 'd' && inputbuf[4] == 'b' && inputbuf[5] == 'y' && inputbuf[6] == 'e') || (inputbuf[0] == 'O' && inputbuf[1] == 'K')))
	  {
	    fprintf(stderr, "ERROR wrong reply from server\n");
	    exit(1);
	  }

      } while(!(inputbuf[0] == 'G' && inputbuf[1] == 'o' && inputbuf[2] == 'o' && inputbuf[3] == 'd' && inputbuf[4] == 'b' && inputbuf[5] == 'y' && inputbuf[6] == 'e'));

    return 0;

}
