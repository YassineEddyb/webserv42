#include "client.hpp"

Client::Client()
{
    std::cout << "Client was Created" << std::endl;
    addr_len = sizeof(addr);
    received = 0;
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

Client::~Client()
{
    std::cout << "Client was Destroyed" << std::endl;
}