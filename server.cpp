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
  const int enable = 1;
  std::cout << "Creating a Socket..." << std::endl;
  sockfd = socket(bind_address->ai_family, bind_address->ai_socktype, bind_address->ai_protocol);
  if (sockfd == -1)
  {
    std::cerr << "socket: " << strerror(errno) << std::endl;
    exit(1);
  }
  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
  {
    std::cerr << "setsockopt: " << strerror(errno) << std::endl;
    exit(1);
  }
}

void Server::bind_socket()
{
  std::cout << "Binding the socket with info address..." << std::endl;
  if (bind(sockfd, bind_address->ai_addr, bind_address->ai_addrlen))
  {
    std::cerr << "bind: " << strerror(errno) << std::endl;
    exit(1);
  }
  freeaddrinfo(bind_address);
}

void Server::listen_on_socket()
{
  std::cout << "listening on the socket..." << std::endl;
  if (listen(sockfd, SOCKET_LISTEN))
  {
    std::cerr << "listen: " << strerror(errno) << std::endl;
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
  Client *c = new Client();
  struct sockaddr_storage addr;
  socklen_t addr_len = sizeof(addr);

  int client_socket = accept(sockfd, (struct sockaddr *)&addr, &addr_len);
  if (client_socket < 0)
  {
    std::cerr << "accept: " << strerror(errno) << std::endl;
    exit(1);
  }

  FD_SET(client_socket, &fds);
  if (client_socket > max_socket)
    max_socket = client_socket;

  c->set_socket_fd(client_socket);
  c->set_address(addr);
  clients.push_back(c);
}

Client *Server::get_client_with_fd(int fd)
{
  std::vector<Client *>::iterator start = clients.begin();

  while (start < clients.end())
  {
    if ((*start)->get_socket_fd() == fd)
    {
      return (*start);
      std::cout << "found client width fd: " << fd << std::endl;
    }
    start++;
  }
  return NULL;
}

void Server::handle_request(int fd)
{
  Client *c = get_client_with_fd(fd); // need a copy constructor

  char buff[BUFFER_SIZE];
  int bytes_received = recv(fd, buff, sizeof(buff), 0);

  if (bytes_received < 1)
  {
    FD_CLR(fd, &fds);
    close(fd);
  }
  else
  {
    c->parse_request(buff, bytes_received);

    // std::cout << buff << std::endl;

    // char res[1024] = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n<h1> hello from the server </h1>";
    // send(c->get_socket_fd(), res, strlen(res), 0);

  }
}

void Server::start()
{
  FD_SET(sockfd, &fds);
  std::cout << "Waiting for connection" << std::endl;
  std::cout << "server listening on port: " << PORT << std::endl;

  while (true)
  {
    fd_set read_fds = fds;
    fd_set write_fds = fds;

    if (select(max_socket + 1, &read_fds, &write_fds, NULL, 0) < 0)
    {
      std::cerr << "select: " << strerror(errno) << std::endl;
      exit(1);
    }

    for (int i = 1; i <= max_socket; i++)
    {
      if (FD_ISSET(i, &read_fds))
      {
        if (i == sockfd)
          add_new_client();
        else
          handle_request(i);
      }
      // else if (FD_ISSET(i, &write_fds))
    }
  }
}


Server::~Server()
{
  std::cout << "Destructor Called" << std::endl;
}