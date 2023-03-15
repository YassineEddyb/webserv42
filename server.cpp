#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <iostream>
#include <string.h>

int main()
{
  int ret;
  struct addrinfo hints;
  struct addrinfo *bind_address;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  std::cout << "Getting info address..." << std::endl;
  if ((ret = getaddrinfo(0, "8080", &hints, &bind_address)))
  {
    std::cerr << gai_strerror(ret) << std::endl;
    return 1;
  }

  std::cout << "Creating a socket..." << std::endl;
  int sockfd = socket(bind_address->ai_family, bind_address->ai_socktype, bind_address->ai_protocol);
  if (sockfd == -1)
  {
    std::cerr << strerror(errno) << std::endl;
    return 1;
  }

  std::cout << "Binding the socket with info address..." << std::endl;
  if (bind(sockfd, bind_address->ai_addr, bind_address->ai_addrlen))
  {
    std::cerr << strerror(errno) << std::endl;
    return 1;
  }
  freeaddrinfo(bind_address);

  std::cout << "listening on the socket..." << std::endl;
  if (listen(sockfd, 10))
  {
    std::cerr << strerror(errno) << std::endl;
    return 1;
  }

  std::cout << "waiting for connections..." << std::endl;
  struct sockaddr sock_addr;
  socklen_t sock_addr_len = sizeof(sock_addr);

  int client_socket = accept(sockfd, &sock_addr, &sock_addr_len);
  if (client_socket == -1)
  {
    std::cerr << strerror(errno) << std::endl;
    return 1;
  }

  std::cout << "client is connected" << std::endl;
  char addr_buff[100];
  getnameinfo(&sock_addr, sock_addr_len, addr_buff, sizeof(addr_buff), 0, 0, NI_NUMERICHOST);
  std::cout << "the address of the client is: " << addr_buff << std::endl;

  std::cout << "reading request" << std::endl;
  char req[1024];
  int bytes_recv = recv(client_socket, req, sizeof(req), 0);
  std::cout << "bytes recieved" << bytes_recv << "\n request is :\n"
            << req << std::endl;

  std::cout << "sending a response..." << std::endl;
  const char *res =
      "HTTP/1.1 200 OK\r\n"
      "Connection: close\r\n"
      "Content-Type: text/plain\r\n\r\n"
      "Local time is: ";
  int bytes_sent = send(client_socket, res, sizeof(res), 0);
  std::cout << "sent " << bytes_sent << "of " << sizeof(res) << std::endl;

  time_t timer;
  time(&timer);
  char *time_msg = ctime(&timer);
  bytes_sent = send(client_socket, time_msg, strlen(time_msg), 0);
  std::cout << "sent " << bytes_sent << " of " << sizeof(*time_msg) << std::endl;

  std::cout << "closing connection" << std::endl;
  close(client_socket);

  return 0;
}
