/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_mothod.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiouane <adiouane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 18:32:00 by adiouane          #+#    #+#             */
/*   Updated: 2023/04/25 18:32:00 by adiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../response.hpp"
#include <dirent.h>

void handle_delete(Client *c, char *argv)
{
    std::string location = c->get_request().get_location();
    if (location[0] == '/' && location.length() > 1)
        location.erase(0, 1);
    if (location[0] == '/' && location.length() > 1)
        location.erase(0, 1);
    else if (location.length() == 1 && location[0] == '/')
        location = "root/index.html"; // TODO: change this to ROOT CONFIG
    
    std::cout << "Location: " << location << std::endl;
    std::string response;
    int status_code;
    
    // Check if the resource exists
    if (access(location.c_str(), F_OK) == -1) {
        status_code = 404; // Not Found
        response = "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n";
    } else {
        // Delete the resource
        if (remove(location.c_str()) != 0) {
            status_code = 500; // Internal Server Error
            response = "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 0\r\n\r\n";
        } else {
            status_code = 200; // OK
            response = "HTTP/1.1 200 OK\r\nContent-Length: 0\r\n\r\n";
        }
        // check if the directory is empty and delete it if it is
        
        std::string dir = location.substr(0, location.find_last_of("/"));
        if (dir != "root" && dir != "root/") {
            DIR *dp;
            struct dirent *dirp;
            if ((dp = opendir(dir.c_str())) == NULL) {
                status_code = 500; // Internal Server Error
                response = "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 0\r\n\r\n";
            } else {
                int is_empty = 1;
                while ((dirp = readdir(dp)) != NULL) {
                    if (strcmp(dirp->d_name, ".") != 0 && strcmp(dirp->d_name, "..") != 0) {
                        is_empty = 0;
                        break;
                    }
                }
                closedir(dp);
                if (is_empty) {
                    if (remove(dir.c_str()) != 0) {
                        status_code = 500; // Internal Server Error
                        response = "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 0\r\n\r\n";
                    }
                }
            }
        }    

    }
    
    // Send the response
    send(c->get_socket_fd(), response.c_str(), response.length(), 0);
}

/*
    The curl command is a tool used to transfer data from or to a server, using various network protocols. Here is a breakdown of the curl command you provided:
    curl: starts the curl command-line tool.
    -v: verbose mode, which displays additional information such as headers and status codes.
    -X: specifies the HTTP method to be used for the request. In this case, it's the DELETE method.
    DELETE: the HTTP method to be used for the request.
    http://localhost:8080/root/tst: the URL of the server and the resource path to be deleted.
    Here, localhost refers to the local machine, 8080 is the port number to connect to,
    and /root/tst is the path of the resource to be deleted.
    When you run this command, curl will send an HTTP DELETE request to the server running on localhost at port 8080,
    with the resource path /root/tst. If the request is successful,
    the server will delete the resource and send an HTTP 200 OK response. 
    If the request fails, the server will send an appropriate error response. 
    The -v option is used to display additional information about the request and response in the terminal.
*/