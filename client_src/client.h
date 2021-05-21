#ifndef CLIENT_H
#define CLIENT_H

#include "../common_src/Socket.h"
#include "../common_src/CommunicationProtocol.h"
#include <string>
#include <iostream>

class Client{
private:
    const char* hostname;
    const char* servicename;
    Socket socket;
    //CommunicationProtocol comm;

public:
    char* message;
    int message_length;

    Client(char const *argv[]);
    ~Client();

    void communicate_with_server();
    void init_connection();
    void set_message_length(int len);
    void set_message(char* msg);
    char* get_message();
    int get_message_length();
};

#endif
