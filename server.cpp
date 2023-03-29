#include "server.hpp"

int create_socket()
{
  int ret;
  struct addrinfo hints;
  struct addrinfo *bind_address;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  std::cout << "Getting info address..." << std::endl;
  if ((ret = getaddrinfo(0, PORT, &hints, &bind_address)))
  {
    std::cerr << gai_strerror(ret) << std::endl;
    return 1;
  }

  std::cout << "Creating a socket..." << std::endl;
  int server_socket = socket(bind_address->ai_family, bind_address->ai_socktype, bind_address->ai_protocol);
  if (server_socket == -1)
  {
    std::cerr << strerror(errno) << std::endl;
    return 1;
  }

  std::cout << "Binding the socket with info address..." << std::endl;
  if (bind(server_socket, bind_address->ai_addr, bind_address->ai_addrlen))
  {
    std::cerr << strerror(errno) << std::endl;
    return 1;
  }
  freeaddrinfo(bind_address);

  std::cout << "listening on the socket..." << std::endl;
  if (listen(server_socket, SOCKET_LISTEN))
  {
    std::cerr << strerror(errno) << std::endl;
    return 1;
  }
  return server_socket;
}

int main()
{
  int server_socket = create_socket();
  fd_set fds;
  FD_ZERO(&fds);
  FD_SET(server_socket, &fds);
  int max_socket = SOCKET_LISTEN;

  std::cout << "Waiting for connection" << std::endl;

  while (true)
  {
    fd_set read_fds = fds;

    if (select(max_socket + 1, &read_fds, NULL, NULL, 0) < 0)
    {
      std::cerr << strerror(errno) << std::endl;
      return 1;
    }

    for (int i = 1; i <= max_socket; i++)
    {
      if (FD_ISSET(i, &read_fds))
      {
        if (i == server_socket)
        {
          struct sockaddr_storage client_addr;
          socklen_t addr_len = sizeof(client_addr);
          int socket_client = accept(server_socket, (struct sockaddr *)&client_addr, &addr_len);
          if (socket_client < 0)
          {
            std::cerr << strerror(errno) << std::endl;
            return 1;
          }

          std::cout << "client " << i << " connected." << std::endl;

          FD_SET(socket_client, &fds);
          if (socket_client > max_socket)
            max_socket = socket_client;
        }
        else
        {
          char buff[1024];
          int bytes_received = recv(i, buff, sizeof(buff), 0);
          if (bytes_received < 1)
          {
            FD_CLR(i, &fds);
            close(i);
            continue;
          }

          std::cout << std::endl
                    << buff << std::endl;

          char res[1024] = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n<h1> hello from the server </h1>";
          send(i, res, strlen(res), 0);
        }
      }
    }
  }

  close(server_socket);
  return 0;
}