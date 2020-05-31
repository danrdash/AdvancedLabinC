#include "Read_HTTP_Request.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#define BUFFER_SIZE 1024

bool is_full_http_message_recievd(char *http_message, int Interface_side)
{
  int num_of_2_blanck_line_in_a_row = 0;
  bool is_end_of_http_message = false;
  char *http_message_current_place;
  while (!is_end_of_http_message && http_message_current_place != NULL) {
    http_message_current_place = strstr(http_message, "\r\n\r\n");
    if (http_message_current_place != NULL) {
      num_of_2_blanck_line_in_a_row += 1;
      if (Interface_side == CLIENT || num_of_2_blanck_line_in_a_row == 2) {
        is_end_of_http_message = true;
        break;
      }
    }
  }
  return is_end_of_http_message;
}

int calc_num_of_bytes_to_receive(int num_of_bytes_recieved)
{
  return BUFFER_SIZE - num_of_bytes_recieved % BUFFER_SIZE;
}

bool is_need_to_realloc(int num_of_bytes_recieved) { return (num_of_bytes_recieved % (BUFFER_SIZE - 1) == 0); }

int calc_new_size_to_realloc(int num_of_bytes_recieved)
{
  return BUFFER_SIZE * (1 + (num_of_bytes_recieved + 1) / BUFFER_SIZE);
}

char *read_http_request(int socketfd, int *recieved_buffer_size, int Interface_side)
{
  char *recieved_buffer = (char *)calloc(BUFFER_SIZE, sizeof(char));
  int num_of_bytes_recieved = 0;
  while (1) {
    num_of_bytes_recieved += recv(socketfd, (void *)&recieved_buffer[num_of_bytes_recieved],
                                  calc_num_of_bytes_to_receive(num_of_bytes_recieved), 0);
    if (is_need_to_realloc(num_of_bytes_recieved)) {
      recieved_buffer =
          (char *)realloc(recieved_buffer, sizeof(char) * calc_new_size_to_realloc(num_of_bytes_recieved));
    }
    if (is_full_http_message_recievd(recieved_buffer, Interface_side)) {
      break;
    }
  }
  *recieved_buffer_size = num_of_bytes_recieved;
  return recieved_buffer;
}
