#include "server.hpp"

Server::Server()
{
  std::cout << "Server was Created" << std::endl;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  max_socket = SOCKET_LISTEN;
  FD_ZERO(&fds);
}

int Server::get_sokcet_fd()
{
  return sockfd;
}

void Server::get_address_info()
{
  int ret;

  std::cout << "Getting info address..." << std::endl;
  if ((ret = getaddrinfo(0, PORT, &hints, &bind_address)))
  {
    std::cerr << gai_strerror(ret) << std::endl;
    exit(1);
  }
}

void Server::create_socket()
{
  std::cout << "Creating a Socket..." << std::endl;
  sockfd = socket(bind_address->ai_family, bind_address->ai_socktype, bind_address->ai_protocol);
  if (sockfd == -1)
  {
    std::cerr << strerror(errno) << std::endl;
    exit(1);
  }
}

void Server::bind_socket()
{
  std::cout << "Binding the socket with info address..." << std::endl;
  if (bind(sockfd, bind_address->ai_addr, bind_address->ai_addrlen))
  {
    std::cerr << strerror(errno) << std::endl;
    exit(1);
  }
  freeaddrinfo(bind_address);
}

void Server::listen_on_socket()
{
  std::cout << "listening on the socket..." << std::endl;
  if (listen(sockfd, SOCKET_LISTEN))
  {
    std::cerr << strerror(errno) << std::endl;
    exit(1);
  }
}

void Server::create_server()
{
  get_address_info();
  create_socket();
  bind_socket();
  listen_on_socket();
}

void Server::add_new_client()
{
  Client c;
  struct sockaddr_storage addr;
  socklen_t addr_len = sizeof(addr);

  int client_socket = accept(sockfd, (struct sockaddr *)&addr, &addr_len);
  if (client_socket < 0)
  {
    std::cerr << strerror(errno) << std::endl;
    exit(1);
  }

  FD_SET(client_socket, &fds);
  if (client_socket > max_socket)
    max_socket = client_socket;

  c.set_socket_fd(client_socket);
  c.set_address(addr);
  clients.push_back(c);
}

void Server::handle_request(int fd)
{
  char buff[1024] = {0};
  int bytes_received = recv(fd, buff, sizeof(buff), 0);
  if (bytes_received < 1)
  {
    FD_CLR(fd, &fds);
    close(fd);
  }
  else
  {
    std::string req(buff);
    // std::map<std::string, std::string> map = handle_request(req);

    // print_map(map);

    char res[1024] = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n<h1> hello from the server </h1>";
    send(fd, res, strlen(res), 0);
  }
}

void Server::multiplixing()
{
  FD_SET(sockfd, &fds);

  std::cout << "Waiting for connection" << std::endl;

  while (true)
  {
    fd_set read_fds = fds;

    if (select(max_socket + 1, &read_fds, NULL, NULL, 0) < 0)
    {
      std::cerr << strerror(errno) << std::endl;
      exit(1);
    }

    for (int i = 1; i <= max_socket; i++)
    {
      if (FD_ISSET(i, &read_fds))
      {
        if (i == sockfd)
          add_new_client();
        else
      }
    }
  }
}

Server::~Server()
{
  std::cout << "Destructor Called" << std::endl;
}