#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "main.hpp"

class Client
{
private:
  struct sockaddr_storage address;
  socklen_t address_length;
  int socket;
  char request[MAX_REQUEST_SIZE + 1];
  int received;

public:
  Client();

  void set_socket();

  ~Client();
};

#endif