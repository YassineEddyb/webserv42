/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_file.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiouane <adiouane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 02:07:00 by adiouane          #+#    #+#             */
/*   Updated: 2023/04/25 15:48:20 by adiouane         ###   ########.fr       */
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
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;

    while (std::getline(ss, token, ' '))
    {
        if (!token.empty())
            tokens.push_back(token);
    }
    if (tokens[0] == "host:")
    {
        servers.push_back(server());
        servers.back().host = tokens[1];
    }
    else if (tokens[0] == "port:")
        servers.back().port = tokens[1];
    else if (tokens[0] == "max_body_size:")
        servers.back().max_body_size = tokens[1];
    else if (tokens[0] == "server_name:")
    {
        for (size_t i = 1; i < tokens.size(); i++)
            servers.back().server_name.push_back(tokens[i]);
    }
    else if  (tokens[0] == "error_page")
    {
        for (size_t i = 1; i < tokens.size(); i++)
        {
            if (tokens[i] == "400:")
            {
                // if (servers.back().error_page_400.size() != 0)
                //     servers.push_back(server());
                servers.back().error_page_400[tokens[i]] = tokens[i + 1];
            }
            else if (tokens[i] == "404:")
            {
                // if (servers.back().error_page_404.size() != 0)
                //     servers.push_back(server());
                servers.back().error_page_404[tokens[i]] = tokens[i + 1];
            }
        }
    }
    else if (tokens.size() == 3 && tokens[0] == "server_name:")
    {
        for (size_t i = 1; i < tokens.size(); i++)
            servers.back().server_name.push_back(tokens[i]);
    }
    else
        return;

}


void ConfigFile::parseLocation(const std::string &line)
{
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;

    while (std::getline(ss, token, ' '))
    {
        if (!token.empty())
            tokens.push_back(token);
    }
    if (tokens[0] == "}")
        return;
    else if (tokens[0] == "root:")
        servers.back().locations.back().root = tokens[1];
    else if (tokens[0] == "index:")
    {
        for (size_t i = 1; i < tokens.size(); i++)
            servers.back().locations.back().index.push_back(tokens[i]);
    }
    else if (tokens[0] == "autoindex:")
        servers.back().locations.back().autoindex = tokens[1];
    else if (tokens.size() == 3 && tokens[0] == "cgi_path:")
    {
        servers.back().locations.back().cgi_path[tokens[1]] = tokens[2];
    }
    else if (tokens[0] == "methods:")
    {
        for (size_t i = 1; i < tokens.size(); i++)
            servers.back().locations.back().methods.push_back(tokens[i]);
    }
    else if (tokens[0] == "return:")
        servers.back().locations.back().return_ = tokens[1];
    else if (tokens[0] == "upload_path:")
        servers.back().locations.back().upload_path = tokens[1];
    else
        return;
}

ConfigFile::ConfigFile(const std::string &filename) // like argv[1]
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
            if (line.find("server {") != std::string::npos)
            {
                i = 1;
                continue;
            }
            if (line.find("location") != std::string::npos)
            {
                servers.back().locations.push_back(location()); // default location initialization
                std::istringstream iss(line);
                std::vector<std::string> words;
                std::string word;
                while (iss)
                {
                    std::string word;
                    iss >> word;
                    words.push_back(word);
                }
                for (size_t i = 1; i < words.size(); i++)
                {
                    // earse } from location_config
                    if (words[i].find("}") != std::string::npos)
                        words[i].erase(words[i].find("}"));
                    else if (words[i].find("{") != std::string::npos)
                        words[i].erase(words[i].find("{"));
                    servers.back().locations.back().location_config.push_back(words[i]);
                }
                i = 2;
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
