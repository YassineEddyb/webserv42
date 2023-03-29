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
  int server_socket, client_socket;
  socklen_t addr_size;
  struct sockaddr_in server_addr, client_addr;
  int port = 8080;
  char response[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE html>\n<html>\n<head>\n<title>Hello, World!</title>\n</head>\n<body>\n<h1>Hello, World!</h1>\n</body>\n</html>\n";
  int response_size = sizeof(response);

  // Create a socket
  server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (server_socket < 0)
  {
    std::cerr << "Failed to create socket\n";
    return 1;
  }

  // Bind the socket to a port
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  server_addr.sin_addr.s_addr = INADDR_ANY;
  if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
  {
    std::cerr << "Failed to bind socket to port " << port << "\n";
    return 1;
  }

  // Listen for incoming connections
  if (listen(server_socket, 5) < 0)
  {
    std::cerr << "Failed to listen for incoming connections\n";
    return 1;
  }

  std::cout << "Server listening on port " << port << "\n";

  while (true)
  {
    // Accept incoming connections
    addr_size = sizeof(client_addr);
    client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_size);
    if (client_socket < 0)
    {
      std::cerr << "Failed to accept incoming connection\n";
      continue;
    }

    // Send the response to the client
    if (send(client_socket, response, response_size, 0) != response_size)
    {
      std::cerr << "Failed to send response to client\n";
    }

    // Close the client socket
    close(client_socket);
  }

  // Close the server socket
  close(server_socket);

  return 0;
}