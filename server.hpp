#ifndef SERVER_HPP
#define SERVER_HPP

#include "main.hpp"
#include "./parsing/parsing.hpp"
#include "client.hpp"

class Server
{
private:
  int sockfd;
  struct addrinfo hints;
  struct addrinfo *bind_address;
  int max_socket;
  fd_set fds;
  std::vector<Client> clients;

public:
  Server();

  int get_sokcet_fd();

  void get_address_info();
  void create_socket();
  void bind_socket();
  void listen_on_socket();
  void create_server();
  void add_new_client();
  void handle_request(int fd);
  void multiplixing();

  ~Server();
};

#endif