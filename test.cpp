#include <iostream>
#include <string>

int main()
{
  char buff[20] = "hello world";
  std::cout << buff << std::endl;
  std::string str(buff);
  std::cout << str << std::endl;
}