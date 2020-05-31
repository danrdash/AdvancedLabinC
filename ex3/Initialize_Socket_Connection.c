#include "Initialize_Socket_Connection.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#define MAX_PORT 64000
#define MIN_PORT 1025
#define LISTEN_CAPACITY 10
#define SOCKET_ERROR -1

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
  int result_serverfd = 0;
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

void Initialize_Socket_Connection(int *fd, FILE *fp)
{
  int enable = true, *randPort;
  struct sockaddr_in *serv_addr;
  *randPort = 0;

  // https://cboard.cprogramming.com/c-programming/145187-how-pick-random-number-between-x-y.html how to find a random
  // nubmer  between two integers
  *randPort = (rand() % (MAX_PORT - MIN_PORT)) + MIN_PORT;
  *fd = socket(AF_INET, SOCK_STREAM, 0);
  serv_addr = createSockaddr_in(*randPort);
  setsockopt(*fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
  serv_addr = findPort(*fd, serv_addr, randPort);
  listen(*fd, LISTEN_CAPACITY);
  fprintf(fp, "%d", *randPort);
  free(serv_addr);
  fclose(fp);
  return;
}
