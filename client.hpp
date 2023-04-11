#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "main.hpp"

class Client
{
private:
  struct sockaddr_storage addr;
  socklen_t addr_len;
  int socket_fd;
  int received;
  Request req;

public:
  Client();

  void set_socket_fd(int fd);
  void set_address(struct sockaddr_storage &address);
  int get_socket_fd();
  void set_received(int rec);

  ~Client();
};

#endif