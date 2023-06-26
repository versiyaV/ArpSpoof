#ifndef _SOCKET_H
#define _SOCKET_H
#include <map>
#include <string>

namespace Socket 
{
    extern std::map<std::string, int> sockets;
    int open_socket(const std::string &ip);
    void bind_socket(int sd, const std::string &interface_name);
    int get_interface_index(int sd, const std::string &interface_name);
    void close_sockets();
}

#endif