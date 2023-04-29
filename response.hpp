/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiouane <adiouane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 05:41:07 by adiouane          #+#    #+#             */
/*   Updated: 2023/04/11 05:41:07 by adiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include <iostream>
# include <string>
# include "server.hpp"
# include "request.hpp"
# include "config/config_file.hpp"
#include <fcntl.h>



void    handle_response(Client *client, char *argv);
void    sent_error(int client_socket, int code);
void    handle_get(Client *client, char *argv);
std::string getContentType(std::string &filename);
//void    sent_file(Client *c, std::string file, std::string contentType);
// int    is_allowed_method(std::string method, std::vector<std::string> &methods);

int is_request_in_location(std::string request, Client *c,  char *argv);

/*--------------------------Delere method--------------------------*/
void handle_delete(Client *c, char *argv);
void send_response(Client *c, char *argv);

#endif