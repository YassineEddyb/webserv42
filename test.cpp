#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "client.hpp"

// std::string body;

// std::string decode_chunked(std::string input) {
//   static int chunk_size = 0;
//   static std::string temp;
//   std::string chunk;

//   input.insert(0, temp);

//   while(input.length() > 0) {
//     if (chunk_size >= input.length()) {
//       chunk.append(input);
//       chunk_size -= input.length();
//       break;
//     } else {
//       if (chunk_size > 0) {
//         chunk.append(input.substr(0, chunk_size));
//         input = input.substr(chunk_size, input.length() - chunk_size);
//       }

//       int start = 2;
//       int pos = input.find("\r\n", start);
//       if (pos == std::string::npos) {
//         temp = input;
//         chunk_size = 0;
//         break;
//       }
//       std::string chunk_size_str = input.substr(start, pos - start);
//       std::cout << "chunk size: " << chunk_size_str << std::endl;
//       chunk_size = std::stoi(chunk_size_str, nullptr, 16);
//       if (chunk_size == 0)
//         break;
//       input = input.substr(pos + 2, input.length() - pos - 2);

//     }
//   }

//   body.append(chunk);
//   return chunk;
// }

void print_string(std::string label, std::string str) {
  std::cout << label;
  for(int i = 0 ; i < str.length(); i++) {
    if (str[i] == '\n')
      std::cout << "/n";
    else if (str[i] == '\r')
      std::cout << "/r";
    else std::cout << str[i];
  }

  std::cout << std::endl;
}

std::string body;

std::string decode_chunked(const char* input, size_t length) {
  static int chunk_size = 0;
  static std::string temp;
  std::string chunk;

  std::string str_input(input, length);
  str_input.insert(0, temp);
  temp = "";

  print_string("body: ", str_input);

  while(str_input.length() > 0) {
    if (chunk_size >= str_input.length()) {
      chunk.append(str_input);
      chunk_size -= str_input.length();
      break;
    } else {
      if (chunk_size > 0) {
        chunk.append(str_input.substr(0, chunk_size));
        print_string("append: ", str_input.substr(0, chunk_size));
        // str_input = str_input.substr(chunk_size, str_input.length() - chunk_size);
        str_input = str_input.substr(chunk_size, str_input.length() - chunk_size);
        print_string("input: ", str_input);
      }

      int start = 2;
      int pos = str_input.find("\r\n", start);
      if (pos == std::string::npos) {
        temp = str_input;
        chunk_size = 0;
        break;
      }
      std::string chunk_size_str = str_input.substr(start, pos - start);
      std::cout << "chunk size: " << chunk_size_str << std::endl;
      chunk_size = std::stoi(chunk_size_str, nullptr, 16);
      if (chunk_size == 0)
        break;
      str_input = str_input.substr(pos + 2, str_input.length() - pos - 2);
    }
  }

  print_string("temp: ", temp);
  std::cout << "\n\n";

  body.append(chunk);
  return chunk;
}


int main() {
  char input[21] = "\r\nb\r\nHello world\r\n9\r";
  char input1[7] = "\n yass";
  char input2[12] = "\r\nin\r\n0\r\n\r\n";
  // std::cout << decode_chunked("\r\n137e\r\nHel") << std::endl;
  // std::cout << decode_chunked("lo\r\n") << std::endl;
  // std::cout << decode_chunked("a\r\n world yas") << std::endl;
  // std::cout << decode_chunked(input) << std::endl;

  decode_chunked(input, 20);
  decode_chunked(input1, 6);
  decode_chunked(input2, 11);

  std::cout << "\nbody: \n" << body << std::endl;
  return 0;
}