/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiouane <adiouane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 22:39:45 by adiouane          #+#    #+#             */
/*   Updated: 2023/04/24 08:22:53 by adiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
   for (size_t i = 0; i < 2; i++)
   {
    std::cout << "host: " << config.servers[i].host << std::endl;
    std::cout << "port: " << config.servers[i].port << std::endl;
    std::cout << "max_body_size: " << config.servers[i].max_body_size << std::endl;
    std::cout << "server_name: ";
    for (size_t j = 0; j < config.servers[i].server_name.size(); j++)
      std::cout << config.servers[i].server_name[j] << " ";
    std::cout << std::endl;
    std::cout << "error_page 400: ";
    print_map(config.servers[i].error_page_400);
    std::cout << "error_page 404: ";
    print_map(config.servers[i].error_page_404);
    std::cout << "locations: " << std::endl;
    for (size_t j = 0; j < config.servers[i].locations.size(); j++)
    {
      std::cout << "path: " << config.servers[i].locations[j].location_config[0] << std::endl;
      std::cout << "root: " << config.servers[i].locations[j].root << std::endl;
      for (size_t k = 0; k < config.servers[i].locations[j].index.size(); k++)
        std::cout << config.servers[i].locations[j].index[k] << " ";
      std::cout << "autoindex: " << config.servers[i].locations[j].autoindex << std::endl;
      std::cout << "cgi_path: " << config.servers[i].locations[j].cgi_path["php"] << std::endl;
      std::cout << "cgi_path: " << config.servers[i].locations[j].cgi_path["py"] << std::endl;
      
      std::cout << "upload_path: " << config.servers[i].locations[j].upload_path << std::endl;
      std::cout << "return: " << config.servers[i].locations[j].return_ << std::endl;
      std::cout << "methods: ";
      for (size_t k = 0; k < config.servers[i].locations[j].methods.size(); k++)
        std::cout << config.servers[i].locations[j].methods[k] << " ";
      std::cout << std::endl;
    }
    
   }
}

int main(int argc, char **argv)
{
  // (void)argc;
  // (void)argv;
  ConfigFile config(argv[1]);

  print_config(config);
  Server srv;
  srv.create_server();
  srv.start(argv[1]);
  return 0;
}