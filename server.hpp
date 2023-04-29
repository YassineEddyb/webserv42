#ifndef SERVER_HPP
#define SERVER_HPP

#include "main.hpp"
#include "./parsing/parsing.hpp"
#include "client.hpp"
#include "response.hpp"
#include "request.hpp"

class Server
{
private:
  int sockfd;
  struct addrinfo hints;
  struct addrinfo *bind_address;
  int max_socket;
  fd_set fds;
  std::vector<Client *> clients;

public:
  Server();

  int get_sokcet_fd();

  void get_address_info();
  void create_socket();
  void bind_socket();
  void listen_on_socket();
  void create_server();
  void add_new_client();
  Client *get_client_with_fd(int fd);
  void handle_request(int fd, char *argv); //TODO: i change. i add char **argv
  void start(char *argv); //TODO: i change. i add char **argv

  //adiouane
  // get all clients
  std::vector<Client *> get_clients();

  ~Server();
};

#endif