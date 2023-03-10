#ifndef NETWORK_H
#define NETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFF_SIZE 4096
#define LINE_LEN 128
#define BACKLOG 8

int server_run(char *argv[]);
int read_file(char buffer[], char path[]);
int file_name_check(char path[]);

#endif // NETWORK_H