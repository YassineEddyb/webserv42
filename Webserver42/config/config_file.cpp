/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_file.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiouane <adiouane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 02:07:00 by adiouane          #+#    #+#             */
/*   Updated: 2023/04/11 01:24:04 by adiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config_file.hpp"

ConfigFile::ConfigFile()
{
    std::cout << "Default constructor called" << std::endl;
}

ConfigFile::~ConfigFile()
{
    std::cout << "Destructor called" << std::endl;
}

void ConfigFile::parseServer(const std::string &line)
{
    std::vector<std::string> v;
    std::stringstream ss(line);
    std::string item;
    while (getline(ss, item, ' '))
        v.push_back(item);
    for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); ++it)
    {
        if (*it == " ")
            continue;
        if (*it == "host")
        {
            server.host = *(++it);
        }
        else if (*it == "port")
        {
            server.port = *(++it);
        }
        else if (*it == "max_client_body_size")
        {
            server.max_body_size = *(++it);
        }
        else if (*it == "error_page")
        {
            std::string error_code = *(++it);
            std::string error_page = *(++it);
            if (error_code == "400")
                server.error_page_400[error_code] = error_page;
            else if (error_code == "404")
                server.error_page_404[error_code] = error_page;
        }
        else if (*it == "server_name")
        {
            for (std::vector<std::string>::iterator it2 = it + 1; it2 != v.end(); ++it2)
            {
                server.server_name.push_back(*it2);
            }
        }
    }
      
}

void ConfigFile::parseLocation(const std::string &line)
{
    std::vector<std::string> v;
    std::stringstream ss(line);
    std::string item;
    while (getline(ss, item, ' '))
        v.push_back(item);
    for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); ++it)
    {
        if (*it == " ")
            continue;
        if (*it == "root")
        {
            server.locations.back().root = *(++it);
        }
        else if (*it == "autoindex")
        {
            server.locations.back().autoindex = *(++it);
        }
        else if (*it == "upload_path")
        {
            server.locations.back().upload_path = *(++it);
        }
        else if (*it == "allow_methods")
        {
            std::vector<std::string> allow_methods;
            for (std::vector<std::string>::iterator it2 = it + 1; it2 != v.end(); ++it2)
            {
                if (*it2 == "}")
                    break;
                allow_methods.push_back(*it2);
            }
            for (std::vector<std::string>::iterator it2 = allow_methods.begin(); it2 != allow_methods.end(); ++it2)
            {
                server.locations.back().allow_method.push_back(*it2);
            }
        }
        else if (*it == "index")
        {
            std::vector<std::string> index;
            for (std::vector<std::string>::iterator it2 = it + 1; it2 != v.end(); ++it2)
            {
                if (*it2 == "}")
                    break;
                index.push_back(*it2);
            }
            for (std::vector<std::string>::iterator it2 = index.begin(); it2 != index.end(); ++it2)
            {
                server.locations.back().index.push_back(*it2);
            }
        }
        else if (*it == "cgi_path")
        {
            std::string cgi_path = *(++it);
            std::string cgi_extension = *(++it);
            server.locations.back().cgi_path[cgi_extension] = cgi_path;
        }
        else if (*it == "path_file")
        {
            std::string path_file = *(++it);
            server.locations.back().path_file.push_back(path_file);
        }
    }
}

ConfigFile::ConfigFile(const std::string &filename)
{
    std::ifstream file(filename.c_str());
    std::string line;
    int i = 0;
    int j = 0;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            if (line.empty() || line[0] == '#')
                continue;
            if (line.find("server") != std::string::npos && line.find("{") != std::string::npos)
            {
                i = 1;
                continue;
            }
            if (line.find("location") != std::string::npos)
            {
                i = 2;
                //save path_file location /loc2/file.txt 
                // we will save /loc2/file.txt in server.locations.back().path_file
                // first init location struct
                server.locations.push_back(location());
                std::string path_file = line.substr(line.find_first_of("/"), line.find_last_of("{"));
                std::string path = path_file.substr(0, path_file.find_last_of("{"));
                server.locations.back().path_file.push_back(path);
                continue;
            }
            if (i == 1)
                parseServer(line);
            else if (i == 2)
                parseLocation(line);
            else
                std::cout << "Error: " << line << std::endl;
        }
        file.close();
    }
    else
    {
        std::cout << "Unable to open file" << std::endl;
    }
}
