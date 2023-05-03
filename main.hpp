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
#include <fstream>

#define PORT "8011"
#define SOCKET_LISTEN 10
// #define MAX_REQUEST_SIZE 1024
#define BUFFER_SIZE 4096

void print_map(std::map<std::string, std::string> map);

#endif