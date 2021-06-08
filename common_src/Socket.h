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

#define FAMILY AF_INET
#define PROTOCOL 0
#define SOCK_TYPE SOCK_STREAM
#define SERVER_FLAGS AI_PASSIVE
#define CLIENT_FLAGS 0

class Socket{
private:
    int fd;
    Socket(const Socket& other) = delete;
    Socket& operator=(const Socket& other) = delete;

public: 
    Socket();
    Socket(const int& family,const int& socktype,const int& protocol);
    ~Socket();
    Socket(Socket&& other);
    Socket& operator=(Socket &&other);
    

    void socket_init(int family,int socktype,int protocol);
    bool bind_and_listen(const char *hostname,const char *servicename);
    int socket_accept(Socket* peer);
    void socket_connect(const char* hostname, const char* servicename);
    ssize_t socket_send(const char* msg,int length);
    int socket_receive(int length, char* buffer);
    void socket_close();
    void socket_shutdown();
};

#endif
