#include "client.hpp"

Client::Client()
{
    std::cout << "Client was Created" << std::endl;
    addr_len = sizeof(addr);
}

void Client::set_socket_fd(int fd)
{
    socket_fd = fd;
}

void Client::set_address(struct sockaddr_storage &address)
{
    addr = address;
}

Client::~Client()
{
    std::cout << "Client was Destroyed" << std::endl;
}