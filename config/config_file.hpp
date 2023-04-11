/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_file.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiouane <adiouane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 01:45:31 by adiouane          #+#    #+#             */
/*   Updated: 2023/04/10 06:58:54 by adiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_FILE_HPP
#define CONFIG_FILE_HPP

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <string.h>


class ConfigFile
{
public:
    ConfigFile();
    ~ConfigFile();
    ConfigFile(const std::string &filename);

    typedef struct
    {
        std::string root;
        std::string autoindex;
        std::string upload_path;
        std::vector<std::string> allow_method;
        std::vector<std::string> index;
        std::map<std::string, std::string> cgi_path;
        std::vector<std::string> path_file;
    } location;
    struct
    {
        std::string host;
        std::string port;
        std::string max_body_size;
        std::map<std::string, std::string> error_page_400;
        std::map<std::string, std::string> error_page_404;
        std::vector<std::string> server_name;
        // declare vector of location
        std::vector<location> locations;
    } server;

private:
    void parseServer(const std::string &line);
    void parseLocation(const std::string &line);
};

#endif