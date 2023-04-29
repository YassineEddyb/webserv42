/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiouane <adiouane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 05:40:43 by adiouane          #+#    #+#             */
/*   Updated: 2023/04/11 05:40:43 by adiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "response.hpp"
#include "request.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <map>
#include <unistd.h>
#include <fcntl.h>
#include "config/config_file.hpp"


void handle_response(Client *c, char *argv)
{
    std::string method = c->get_request().get_method();
    if (method == "GET")
        handle_get(c, argv);
    // else if (method == "POST")
        // handle_post(client_socket,argv);
    else if (method == "DELETE")
        handle_delete(c, argv);
    else
        std::cout << "Method not allowed" << std::endl;
}
