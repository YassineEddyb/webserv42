/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response_handler.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiouane <adiouane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 07:05:42 by adiouane          #+#    #+#             */
/*   Updated: 2023/04/15 07:05:42 by adiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../response.hpp"
#include <sys/stat.h>
#include "../server.hpp"


void send_response(Client *c, char *argv){
    std::string file = c->_fileName;
    std::cout << "file on send: " << file << std::endl;

    
    std::ifstream file1(file); // open the file in read mode
    std::stringstream buffer;  // create a buffer to store the file content
    buffer << file1.rdbuf();   // read the file in buffer and close it automaticly . rdbuf() is a function that return the buffer of the file
    std::string content = buffer.str();
    std::string response = "HTTP/1.1 200 OK\r\nContent-Type: " + getContentType(file) + "\r\nContent-Length: " + std::to_string(content.length()) + "\r\n\r\n" + content;
    send(c->get_socket_fd(), response.c_str(), response.length(), 0);
    close(c->get_socket_fd());

}


int is_valid_file(std::string file, Client *c, char *argv, int i, int j)
{
    ConfigFile config(argv);
    // loop for all inidex in location and see if it exists
    for (int k = 0; k < config.servers[i].locations[j].index.size(); k++)
    {
        std::string path = config.servers[i].locations[j].root + config.servers[i].locations[j].index[k];
        if (file == "/")
            path = config.servers[i].locations[j].root + config.servers[i].locations[j].index[k];
        if (access(path.c_str(), F_OK) == 0)
        {
            c->_fileName = config.servers[i].locations[j].root;
            if (file == "/")
                c->_fileName += config.servers[i].locations[j].index[k];
            else
                c->_fileName += c->get_request().get_location().erase(0, 1);
            return 1;
        }
    }
    return 0;
}

int is_autoindex_enabled(std::string request, std::string autoindex)
{
    if (autoindex == "on")
        return 1;
    return 0;
}

int is_allowed_method(std::string method, std::vector<std::string> methods)
{
    for (int i = 0; i < methods.size(); i++)
    {
        if (methods[i] == method)
            return 1;
    }
    return 0;
}

int is_request_in_location(std::string request, Client *c,  char *argv)
{
    std::cout << "is request in location" << std::endl;
    ConfigFile config(argv);
    std::vector<std::string> method;
    if (request[0] == '/' && request.size() > 1)
        request.erase(request.find_last_of("/"), request.size());
    for (int i = 0; i < config.servers.size(); i++)
    {
        for (int j = 0; j < config.servers[i].locations.size(); j++)
        {
            if (config.servers[i].locations[j].location_config[0] == request)
            {
                method = config.servers[i].locations[j].methods;
                if (is_allowed_method(c->get_request().get_method(), method) == 0)
                {
                    sent_error(c->get_socket_fd(), 405);
                    return 0;
                }
                if (is_autoindex_enabled(c->get_request().get_location(), config.servers[i].locations[j].autoindex) == 0)
                {
                    sent_error(c->get_socket_fd(), 403);
                    return 0;
                }
                if (is_valid_file(c->get_request().get_location(), c, argv, i, j) == 0)
                {
                    sent_error(c->get_socket_fd(), 404);
                    return 0;
                }
                return 1;
            }
        
        }
    }
    return 0;
}


void handle_get(Client *c, char *argv)
{
    ConfigFile config(argv);
    // save locations in vector
    for (int i = 0; i < config.servers.size(); i++)
    {
        for (int j = 0; j < config.servers[i].locations.size(); j++)
        {
            std::cout << "handle get" << std::endl;
            if (is_request_in_location(c->get_request().get_location(), c, argv) == 1)
            {
               c->set_is_valid(1);
               return;
            }
            else
                sent_error(c->get_socket_fd(), 404);
        }
    }
}