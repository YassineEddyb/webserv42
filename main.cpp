#include "server.hpp"

void print_map(std::map<std::string, std::string> map)
{
  for (auto &t : map)
    std::cout << "{" << t.first << ": "
              << t.second << "}" << std::endl;
}

int main()
{
  Server srv;
  srv.create_server();
  srv.multiplixing();

  return 0;
}