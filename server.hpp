#ifndef SERVER_HPP
#define SERVER_HPP

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
#include "./parsing/parsing.hpp"

#define PORT "8080"
#define SOCKET_LISTEN 10

class Server
{
private:
  int sockfd;
  struct addrinfo hints;
  struct addrinfo *bind_address;
  int max_socket;
  fd_set fds;

public:
  Server();

  int get_sokcet_fd();

  void get_address_info();
  void create_socket();
  void bind_socket();
  void listen_on_socket();
  void create_server();
  void add_new_client();
  void multiplixing();

  ~Server();
};

#endif