#ifndef EX3_LB_H
#define EX3_LB_H

#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define ZERO 0
#define SERVER_ARRAY_SIZE 3
#define SOCKET_ERROR -1

void acceptServerSockets(int* server_array, int serverfd, int current_server);
void Initialize_Connection_Routine(int* serverfd, struct sockaddr_in* serv_addr, int* randPort, FILE* server_fp);
void loadBalance(int* web_browserfd, int httpfd, char* recieve_buffer_pointer, int* current_server, int* server_array,
                 char* recieve_buffer_from_server_pointer);

#endif
