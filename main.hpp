#ifndef MAIN_HPP
#define MAIN_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <map>
#include <vector>

#define PORT "8080"
#define SOCKET_LISTEN 10
#define MAX_REQUEST_SIZE 1024



void print_map(std::map<std::string, std::string> map);


#endif