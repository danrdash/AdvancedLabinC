#ifndef READ_HTTP_REQUEST_H
#define READ_HTTP_REQUEST_H

enum Interface_side { CLIENT = 1, SERVER };
char* read_http_request(int socketfd, int* recieved_buffer_size, int Interface_side);

#endif
