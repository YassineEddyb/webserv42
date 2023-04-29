#include "server.hpp"
#include "config/config_file.hpp"

void print_map(std::map<std::string, std::string> map)
{
  for (auto &t : map)
    std::cout << "{" << t.first << ": "
              << t.second << "}" << std::endl;
}

void print_config(ConfigFile &config)
{
  std::cout << "Host: " << config.server.host << std::endl;
  std::cout << "Port: " << config.server.port << std::endl;
  std::cout << "Max body size: " << config.server.max_body_size << std::endl;
  std::cout << "----------Error page 400: ------------" << std::endl;
  print_map(config.server.error_page_400);
  std::cout << "-----------Error page 404: -----------" << std::endl;
  print_map(config.server.error_page_404);
  std::cout << "---------Server name:-------------" << std::endl;
  for (auto &t : config.server.server_name)
    std::cout << t << std::endl;
  std::cout << "*************************************************************" << std::endl;
  for (auto &t : config.server.locations)
  {
    // for (auto &u : t.path_file)
      // std::cout << "Path: " << u << std::endl;
    std::cout << "-----------location------------" << std::endl << t.path_file[0] << std::endl;
    std::cout << "-------------Root--------------"  << std::endl << t.root << std::endl;
    std::cout << "------------Autoindex----------"  << std::endl << t.autoindex << std::endl;
    std::cout << "-----------Upload path--------- "  << std::endl << t.upload_path << std::endl;
    std::cout << "----------Allow method--------- " << std::endl  << std::endl;
    for(std::vector<std::string>::iterator it = t.allow_method.begin(); it != t.allow_method.end(); ++it)
      std::cout << *it << std::endl;
    std::cout << "------------index--------------" << std::endl;
    for(std::vector<std::string>::iterator it = t.index.begin(); it != t.index.end(); ++it)
      std::cout << *it << std::endl;
    std::cout << "-----------cgi_path------------" << std::endl;
    print_map(t.cgi_path);
  std::cout << "*************************************************************" << std::endl;
  }
}

int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;
  // ConfigFile config(argv[1]);
  // print_config(config);
  Server srv;
  srv.create_server();
  srv.start();
  return 0;
}