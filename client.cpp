#include "client.hpp"

Client::Client() {
    std::cout << "Client was Created" << std::endl;
    address_length = sizeof(address);
}

Client::~Client() {
    std::cout << "Client was Destroyed" << std::endl;
}