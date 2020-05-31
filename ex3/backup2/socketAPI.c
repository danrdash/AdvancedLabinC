#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	SOCKET sock = INVALID_SOCKET;
	int iResult = 0;
	
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	printf("%d", iResult);
	
}
