#include "Initialize_Socket_Connection.h"
#include "Read_HTTP_Request.h"
#include <stdlib.h>
#include <sys/socket.h>

#define SERVER_ARRAY_SIZE 3
void acceptServerSockets(int* server_array, int serverfd, int current_server)
{
  for (int index = 0; index < SERVER_ARRAY_SIZE; index++) {
    server_array[index] = accept(serverfd, (struct sockaddr*)NULL, NULL);
  }
}

int main(int argc, char* argv[])
{
  int serverfd = 0, httpfd = 0, current_server = 0, web_browserfd = 0;
  int server_array[SERVER_ARRAY_SIZE] = {0};
  FILE* server_fp = fopen("server_port", "w");
  FILE* http_fp = fopen("http_port", "w");
  char* recieved_buffer;
  int recieved_buffer_size;

  Initialize_Socket_Connection(&serverfd, server_fp);  // remove all arguments except serverfd, and httpfd
  Initialize_Socket_Connection(&httpfd, http_fp);

  acceptServerSockets(server_array, serverfd, current_server);

  while (1) {
    web_browserfd = accept(httpfd, (struct sockaddr*)NULL, NULL);
    recieved_buffer = read_http_request(web_browserfd, &recieved_buffer_size, CLIENT);
    send(server_array[current_server], recieved_buffer, recieved_buffer_size, 0);
    free(recieved_buffer);
    recieved_buffer = read_http_request(server_array[current_server], &recieved_buffer_size, SERVER);
    send(web_browserfd, recieved_buffer, recieved_buffer_size, 0);
    free(recieved_buffer);
    current_server = (current_server + 1) % SERVER_ARRAY_SIZE;
  }
}
