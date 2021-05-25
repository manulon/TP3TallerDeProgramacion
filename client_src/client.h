#ifndef CLIENT_H
#define CLIENT_H

#include "../common_src/Socket.h"
#include "clientProtocol.h"
#include <string>
#include <iostream>

class Client{
private:
    const char* hostname;
    const char* servicename;
    Socket socket;
    Client_Protocol protocol;

public:
    char* message;
    int message_length;

    Client(char const *argv[]);
    ~Client();

    void communicate_with_server();
    void init_connection();
    void set_message_length(const int& len);
    void set_message(const char* msg);
    char* get_message();
    int get_message_length();
};

#endif
