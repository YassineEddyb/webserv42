#include "client.hpp"

Client::Client()
{
    std::cout << "Client was Created" << std::endl;
    addr_len = sizeof(addr);
    received = 0;
    is_header = true;
}

void Client::set_socket_fd(int fd)
{
    socket_fd = fd;
}

int Client::get_socket_fd()
{
    return socket_fd;
}

void Client::set_received(int rec)
{
    received = rec;
}

void Client::set_address(struct sockaddr_storage &address)
{
    addr = address;
}

void Client::parse_request(const char* req_body, size_t length) {
  std::string str(req_body, length);
  if (is_header) {
    int pos = str.find(SEP);
    std::string header = str.substr(0, pos);
    std::string body = str.substr(pos + 4);

    req.parse_headers(header);
    // req.parse_body(body);
    is_header = false;
  } else {
    // req.parse_body(str);
  }
};

Client::~Client()
{
    std::cout << "Client was Destroyed" << std::endl;
}