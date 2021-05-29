#ifndef SOCKET_H
#define SOCKET_H

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdbool.h>
#include <netdb.h>
#include <errno.h>

#define FAMILY AF_INET
#define PROTOCOL 0
#define SOCK_TYPE SOCK_STREAM
#define SERVER_FLAGS AI_PASSIVE
#define CLIENT_FLAGS 0

class Socket{
public: 
    int fd;

    Socket();
    Socket(const int& family,const int& socktype,const int& protocol);

    void socket_init
    (const int& family,const int& socktype,const int& protocol);
    bool bind_and_listen(const char *hostname,const char *servicename);
    int socket_accept(Socket* peer);
    void socket_connect(const char* hostname, const char* servicename);
    int get_fd();
    void socket_close();
    ~Socket();
};

#endif
