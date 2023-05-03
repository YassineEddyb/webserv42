#include "request.hpp"

Request::Request(): is_first_body(true), is_finished(false) {}

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

std::string Request::decode_chunked(std::string input) {
  static int chunk_size = 0;
  static std::string temp;
  std::string chunk;

  if (is_first_body) {
    std::cout << "First body" << std::endl;
    input.insert(0, "\r\n");
    is_first_body = false;
  }
  input.insert(0, temp);
  temp = "";

  while(input.length() > 0) {
    if (chunk_size >= input.length()) {
      chunk.append(input);
      chunk_size -= input.length();
      break;
    } else {
      if (chunk_size > 0) {
        chunk.append(input.substr(0, chunk_size));
        input = input.substr(chunk_size, input.length() - chunk_size);
      }

      int start = 2;
      int pos = input.find("\r\n", start);
      if (pos == std::string::npos) {
        temp = input;
        chunk_size = 0;
        break;
      }
      std::string chunk_size_str = input.substr(start, pos - start);
      std::cout << "chunk size: " << chunk_size_str << std::endl;
      try {
      chunk_size = std::stoi(chunk_size_str, nullptr, 16);
      } catch (std::exception &err) {
        std::cout << err.what() << std::endl;
        exit(1);
      }
      if (chunk_size == 0) {
        is_finished = true;
        break;
      }
      input = input.substr(pos + 2, input.length() - pos - 2);

    }
  }

  // body.append(chunk);
  return chunk;
}

void Request::parse_body(std::string req_body)
{


  // if (is_finished) {
    // std::cout << body << std::endl;
    std::ofstream file("video.mp4", std::ios_base::app);
    file << decode_chunked(req_body);
    file.close();
  // }

  // std::cout << decode_chunked(req_body) << std::endl;
}

Request::~Request()
{
  std::cout << "Request Destructor Called" << std::endl;
}