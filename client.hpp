#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "server.hpp"

#define MAX_REQUEST_SIZE 1024

class Client
{
private:
  socklen_t address_length;
  struct sockaddr_storage address;
  int socket;
  char request[MAX_REQUEST_SIZE + 1];
  int received;

public:
};

#endif