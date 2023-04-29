#include "request.hpp"

Request::Request() {}

void Request::parse_request_line(std::string req_line)
{
  int pos = req_line.find(SPACE);
  method = req_line.substr(0, pos);

  int new_pos = req_line.find(SPACE, pos + 1);
  location = req_line.substr(pos + 1, new_pos - pos - 1);

}

void Request::parse_headers(std::string header)
{
  int pos = header.find(LINE_SEP) + 2;
  parse_request_line(header.substr(0, pos));

  while (pos < header.length())
  {
    size_t end_pos = header.find(LINE_SEP, pos);
    if (end_pos == std::string::npos)
      end_pos = header.length();

    size_t colon_pos = header.find(COLON, pos);
    if (colon_pos == std::string::npos)
      break;

    std::string key = header.substr(pos, colon_pos - pos);
    std::string value = header.substr(colon_pos + 2, end_pos - colon_pos - 2);

    headers[key] = value;
    pos = end_pos + 2;
  }

  print_map(headers);
}

void Request::parse_body(std::string body)
{
  std::cout << "\n"
            << body << "\n"
            << std::endl;
}

Request::~Request()
{
  std::cout << "Request Destructor Called" << std::endl;
}