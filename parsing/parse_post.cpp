#include "parsing.hpp"

// Parse the body of a POST request and return the key-value pairs as an unordered_map
std::unordered_map<std::string, std::string> parse_post_body(const std::string &body)
{
  std::unordered_map<std::string, std::string> result;

  // Split the body into key-value pairs
  int pos = 0;
  while (pos < body.length())
  {
    // Find the next '&' character
    int amp_pos = body.find('&', pos);
    if (amp_pos == std::string::npos)
    {
      amp_pos = body.length();
    }

    // Extract the key-value pair
    int eq_pos = body.find('=', pos);
    if (eq_pos == std::string::npos || eq_pos > amp_pos)
    {
      // Invalid key-value pair
      pos = amp_pos + 1;
      continue;
    }
    std::string key = body.substr(pos, eq_pos - pos);
    std::string value = body.substr(eq_pos + 1, amp_pos - eq_pos - 1);

    // Add the key-value pair to the result
    result[key] = value;

    // Advance to the next key-value pair
    pos = amp_pos + 1;
  }

  return result;
}

// Parse the HTTP request and return a response
std::string handle_request(const std::string &request)
{
  // Parse the request
  int pos = request.find("\r\n\r\n");
  if (pos == std::string::npos)
  {
    return "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n";
  }
  std::string body = request.substr(pos + 4);
  std::unordered_map<std::string, std::string> post_data = parse_post_body(body);

  // Construct the response
  std::string response_body = "Hello, ";
  auto it = post_data.find("name");
  if (it != post_data.end())
  {
    response_body += it->second;
  }
  else
  {
    response_body += "World";
  }
  std::string response =
      "HTTP/1.1 200 OK\r\n"
      "Content-Type: text/plain\r\n"
      "Content-Length: " +
      std::to_string(response_body.length()) + "\r\n"
                                               "\r\n" +
      response_body;

  return response;
}
