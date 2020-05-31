#!/bin/bash

gcc -std=c99 -Wall server.c -o server 

gcc -std=c99 -Wall client.c -o client
gcc -std=c99  ex3_lb.c -o ex3_lb
./ex3_lb server_port.txt http_port.txt
cat server_port.txt http_port.txt

