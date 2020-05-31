// https://www.thegeekstuff.com/2011/12/c-socket-programming/
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 

void printSockaddr_in(struct sockaddr_in* serv_addr);


void printSockaddr_in(struct sockaddr_in* serv_addr)
{
	printf("family %d\nport %d\nin_addr %d\n", serv_addr->sin_family, serv_addr->sin_port, serv_addr->sin_addr.s_addr);
}

int main(int argc, char *argv[])
{
	int sockfd=0, n=0, connect_result;
	char recvBuff[1024], buff[100], *token;
	struct sockaddr_in serv_addr;
	// FILE *server_fp = fopen("server_port.txt", "r");
	// fgets(buff, 100, server_fp);
	// fclose(server_fp);
	// token = buff;
	// for(;;)
	// {
		// if (*token == '\n'){
			// *token = '\0';
			// break;
		// }
		// token++;
	// }
	
	if (argc != 2)
	{
		printf("\n Usage: %s <ip of server> \n",argv[0]);
        return 1;
	}
	
	memset(recvBuff, '0',sizeof(recvBuff));
	  
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    } 
	
	memset(&serv_addr, '0', sizeof(serv_addr)); 
	
	serv_addr.sin_family = AF_INET;
	//serv_addr.sin_addr.s_addr =htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000);
	//printf("read server port %s from file\n", buff);
  
	 if(inet_pton(AF_INET, 0, &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    } 
	printSockaddr_in(&serv_addr);
	connect_result = connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if( connect_result < 0)
    {
       printf("\n Error : Connect Failed ->%s \n", strerror(errno));
       return 1;
    } 
	
	while ( (n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0)
    {
        recvBuff[n] = 0;
        if(fputs(recvBuff, stdout) == EOF)
        {
            printf("\n Error : Fputs error\n");
        }
    } 
	
	if(n < 0)
    {
		printf("Error is %d\n", n);
		printf("errno is %s\n", strerror(errno));
        printf("\n Read error \n");
    } 

    return 0;
}
