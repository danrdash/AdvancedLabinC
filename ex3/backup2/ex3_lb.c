//ex3_lb

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

#define MAX_PORT 64000
#define MIN_PORT 1025
#define BUFFER_SIZE 0125
struct sockaddr_in* createSockaddr_in(int randPort);
void printSockaddr_in(struct sockaddr_in* serv_addr);


void printSockaddr_in(struct sockaddr_in* serv_addr)
{
	printf("family %d\nport %d\nin_addr %d\n", serv_addr->sin_family, serv_addr->sin_port, serv_addr->sin_addr.s_addr);
}


struct sockaddr_in* createSockaddr_in(int randPort)
{
	struct sockaddr_in *serv_addr=NULL;
	serv_addr = (struct sockaddr_in*)malloc(sizeof(struct sockaddr_in));
	serv_addr->sin_family =AF_INET;
	serv_addr->sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr->sin_port = htons(randPort);
	return serv_addr;
}


int main(int argc, char *argv[])
{
        int serverfd =0, httpfd = 0, randPort=-1, result_serverfd=1, result_httpfd=1;
		int enable=1, server1fd, server2fd, server3fd, web_browserfd;
		time_t time_seed;
        struct sockaddr_in *serv_addr=NULL, *serv_addr2=NULL;
		FILE *server_fp = fopen( argv[1], "w"); //argv[1] is server_port path, argv[2] is http_port path
		FILE *http_fp = fopen( argv[2], "w");
		char sendBuff[BUFFER_SIZE];
		char buffer[BUFFER_SIZE];

		
		
		memset(&serv_addr, '0', sizeof(serv_addr));
        memset(&sendBuff, '0', sizeof(sendBuff));
		
		srand((unsigned) time(&time_seed));
		while(1)
		{
			randPort = (rand() % ( MAX_PORT - MIN_PORT)) +MIN_PORT; //https://cboard.cprogramming.com/c-programming/145187-how-pick-random-number-between-x-y.html
			serverfd = socket(AF_INET, SOCK_STREAM, 0);
			printf("result from socket init %d\n", serverfd);
			serv_addr = createSockaddr_in(randPort);
		
			
			
			setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
			while(1)
			{
			result_serverfd = bind(serverfd, (struct sockaddr*)serv_addr, sizeof(*serv_addr));
			if (result_serverfd == -1){
				printf("entered bind loop \n");
				randPort = (rand() % ( MAX_PORT - MIN_PORT)) +MIN_PORT;
				free(serv_addr);
				serv_addr = createSockaddr_in(randPort);
				continue;
				}
			else
				break;
			}
			listen(serverfd, 10);
			fprintf(server_fp, "%d\n %d %s\n", randPort, result_serverfd, strerror(errno));
			close(serverfd);
			
			
			randPort = (rand() % ( MAX_PORT - MIN_PORT)) +MIN_PORT; //https://cboard.cprogramming.com/c-programming/145187-how-pick-random-number-between-x-y.html
			serv_addr2 = createSockaddr_in(randPort);
			httpfd = socket(AF_INET, SOCK_STREAM, 0);
			printf("result from socket init %d\n", serverfd);
			
			
			setsockopt(httpfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
			while(1)
			{
			result_httpfd = bind(httpfd, (struct sockaddr*)serv_addr2, sizeof(*serv_addr2));
			if (result_httpfd == -1){
				//printf("entered bind loop \n");
				randPort = (rand() % ( MAX_PORT - MIN_PORT)) +MIN_PORT;
				free(serv_addr2);
				serv_addr2 = createSockaddr_in(randPort);
				continue;
				}
			else
				break;
			}
			listen(httpfd, 10);
			fprintf(http_fp, "%d\n %d %s \n", randPort, result_httpfd, strerror(errno));
			fclose(server_fp);
			fclose(http_fp);
			
			
			printSockaddr_in(serv_addr);
			//SET UP PORTS FOR EACH SERVER//
			server1fd = accept(serverfd, (struct sockaddr*)NULL, NULL);
			server2fd = accept(serverfd, (struct sockaddr*)NULL, NULL);
			server3fd = accept(serverfd, (struct sockaddr*)NULL, NULL);
			
			web_browserfd = accept(httpfd, (struct sockaddr*)NULL, NULL);
			
			break;
				
			
			
		}
		
		
		free(serv_addr);
		free(serv_addr2);
		
		

}