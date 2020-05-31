
#include "ex3_lb.h"
#include "recvString.h"
#include <stdlib.h>
#include <string.h>

#define MAX_PORT 64000
#define MIN_PORT 1025
#define LISTEN_CAPACITY 10

struct sockaddr_in *createSockaddr_in(int randPort)
{
  struct sockaddr_in *serv_addr = NULL;
  serv_addr = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
  serv_addr->sin_family = AF_INET;
  serv_addr->sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr->sin_port = htons(randPort);
  return serv_addr;
}

struct sockaddr_in *findPort(int serverfd, struct sockaddr_in *serv_addr, int *randPort)
{
  int result_serverfd = ZERO;
  while (true) {
    result_serverfd = bind(serverfd, (struct sockaddr *)serv_addr, sizeof(*serv_addr));
    if (result_serverfd == SOCKET_ERROR) {
      *randPort = (rand() % (MAX_PORT - MIN_PORT)) + MIN_PORT;
      free(serv_addr);
      serv_addr = createSockaddr_in(*randPort);
      continue;
    } else {
      break;
    }
  }
  return serv_addr;
}

void Initialize_Connection_Routine(int *fd, struct sockaddr_in *serv_addr, int *randPort, FILE *server_fp)

{
  int enable = true;
  // https://cboard.cprogramming.com/c-programming/145187-how-pick-random-number-between-x-y.html how to find a random
  // nubmer  between two integers
  *randPort = (rand() % (MAX_PORT - MIN_PORT)) + MIN_PORT;
  *fd = socket(AF_INET, SOCK_STREAM, ZERO);
  serv_addr = createSockaddr_in(*randPort);
  setsockopt(*fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
  serv_addr = findPort(*fd, serv_addr, randPort);
  listen(*fd, LISTEN_CAPACITY);

  fprintf(server_fp, "%d", *randPort);
  free(serv_addr);
  fclose(server_fp);
  return;
}
void acceptServerSockets(int *server_array, int serverfd, int current_server)
{
  server_array[current_server] = accept(serverfd, (struct sockaddr *)NULL, NULL);
  server_array[current_server + 1] = accept(serverfd, (struct sockaddr *)NULL, NULL);
  server_array[current_server + 2] = accept(serverfd, (struct sockaddr *)NULL, NULL);
}

void loadBalance(int *web_browserfd, int httpfd, char *recieve_buffer_pointer, int *current_server, int *server_array,
                 char *recieve_buffer_from_server_pointer)
{
  *web_browserfd = accept(httpfd, (struct sockaddr *)NULL, NULL);
  recieve_buffer_pointer = recvString(*web_browserfd);

  send(server_array[*current_server], recieve_buffer_pointer, strlen(recieve_buffer_pointer), 0);
  recieve_buffer_from_server_pointer = recvString(server_array[*current_server]);

  send(*web_browserfd, recieve_buffer_from_server_pointer, strlen(recieve_buffer_from_server_pointer), 0);
  close(*web_browserfd);

  *current_server = ((*current_server + 1) % SERVER_ARRAY_SIZE);
}
