#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "main.hpp"
#include "request.hpp"

class Client
{
private:
  struct sockaddr_storage addr;
  socklen_t addr_len;
  int socket_fd;
  int received;
  Request req;
  bool is_header;
  //adiouane
  bool is_valid = false;
public:
  Client();

  void set_socket_fd(int fd);
  void set_address(struct sockaddr_storage &address);
  int get_socket_fd();
  void set_received(int rec);
  void parse_request(std::string req);
  // get request
  Request get_request();
  bool get_is_valid();
  void set_is_valid(bool valid);
  std::string _fileName;


  ~Client();
};

#endif