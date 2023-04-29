/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_utils.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiouane <adiouane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 08:17:30 by adiouane          #+#    #+#             */
/*   Updated: 2023/04/24 08:17:30 by adiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../response.hpp"

int    is_allowed_method(std::string method, std::vector<std::string> &methods)
{
    if (std::find(methods.begin(), methods.end(), method) == methods.end())
        return (0);
    return (1);
}

void sent_error(int client_socket, int code)
{
    /*
       If you use int instead of static const int, every time the function is called,
       the integer value will be created and stored in memory,
       which can cause unnecessary memory usage and reduce performance.

        Using static const int ensures that the value is only created once
        and stored in memory as a constant, which can be accessed by all instances of the function
        without needing to create a new copy. This can help optimize memory usage
        and improve performance. Additionally, using a constant instead of a literal
        value can make the code more readable and easier to maintain.
    */
    static const std::map<int, std::string> response_map = {
        {400, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/html\r\nContent-Length: 0\r\n\r\n"},
        {403, "HTTP/1.1 403 Forbidden\r\nContent-Type: text/html\r\nContent-Length: 21\r\n\r\nautoindex not enabled"},
        {404, "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\nContent-Length: 20\r\n\r\nError 404: Not Found"},
        {405, "HTTP/1.1 405 Method Not Allowed\r\nContent-Type: text/html\r\nContent-Length: 19\r\n\r\n Method Not Allowed"},
        {413, "HTTP/1.1 413 Request Entity Too Large\r\nContent-Type: text/html\r\nContent-Length: 0\r\n\r\n"},
        {414, "HTTP/1.1 414 Request-URI Too Long\r\nContent-Type: text/html\r\nContent-Length: 0\r\n\r\n"},
        {500, "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/html\r\nContent-Length: 0\r\n\r\n"},
        {501, "HTTP/1.1 501 Not Implemented\r\nContent-Type: text/html\r\nContent-Length: 0\r\n\r\n"},
        {503, "HTTP/1.1 503 Service Unavailable\r\nContent-Type: text/html\r\nContent-Length: 0\r\n\r\n"},
        {505, "HTTP/1.1 505 HTTP Version Not Supported\r\nContent-Type: text/html\r\nContent-Length: 0\r\n\r\n"},
        {1337, "HTTP/1.1 1337\r\nContent-Type: text/html\r\nContent-Length: 30\r\n\r\n welcome to the our server "}
    };

    std::map<int, std::string>::const_iterator it = response_map.find(code);
    if (it == response_map.end()) {
        std::cout << "Error code not valid" << std::endl;
        return;
    }

    const std::string& response = it->second;
    send(client_socket, response.c_str(), response.length(), 0);
}

std::string getContentType(std::string &filename)
{
    static std::map<std::string, std::string> contentTypeMap;
    if (contentTypeMap.empty())
    {
        contentTypeMap[".html"] = "text/html";
        contentTypeMap[".png"] = "image/png";
        contentTypeMap[".mp4"] = "video/mp4";
        contentTypeMap[".mp3"] = "audio/mpeg";
        contentTypeMap[".css"] = "text/css";
        contentTypeMap[".js"] = "text/javascript";
        contentTypeMap[".json"] = "application/json";
        contentTypeMap[".xml"] = "application/xml";
        contentTypeMap[".pdf"] = "application/pdf";
        contentTypeMap[".zip"] = "application/zip";
        contentTypeMap[".txt"] = "text/plain";
        contentTypeMap[".gif"] = "image/gif";
        contentTypeMap[".jpg"] = "image/jpeg";
        contentTypeMap[".svg"] = "image/svg+xml";
        contentTypeMap[".wav"] = "audio/wav";
        contentTypeMap[".mpg"] = "video/mpeg";
        contentTypeMap[".mov"] = "video/quicktime";
        contentTypeMap[".avi"] = "video/x-msvideo";
    }

    std::string contentType = "text/plain";
    std::string extension = filename.substr(filename.find_last_of("."));
    if (contentTypeMap.count(extension) > 0)
    {
        contentType = contentTypeMap[extension];
        return contentType;
    }
    return contentType;
}

