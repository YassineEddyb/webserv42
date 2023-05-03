#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "main.hpp"
#define SEP "\r\n\r\n"
#define LINE_SEP "\r\n"
#define COLON ": "
#define SPACE ' '
#define POST "POST"
#define GET "GET"
#define DELETE "DELETE"

class Request
{
private:
  std::string method;
  std::string location;
  std::map<std::string, std::string> headers;
  std::string body;
  bool is_first_body;
  bool is_finished;

public:
  Request();

  void parse_headers(std::string header);
  void parse_request_line(std::string req_line);
  std::string decode_chunked(std::string input);
  void parse_body(std::string req_body);

  ~Request();
};

#endif