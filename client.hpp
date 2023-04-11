#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "main.hpp"

class Client
{
private:
  struct sockaddr_storage addr;
  socklen_t addr_len;
  int socket_fd;
  char request[MAX_REQUEST_SIZE + 1];
  int received;
  // Request req;

public:
  Client();

  void set_socket_fd(int fd);
  void set_address(struct sockaddr_storage &address);

  ~Client();
};

#endif