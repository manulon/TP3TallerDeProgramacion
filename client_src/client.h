#ifndef CLIENT_H
#define CLIENT_H

#include "../common_src/Socket.h"

class Client{
private:
    const char* hostname;
    const char* servicename;
    Socket socket;

public:
    char* message;
    int message_length;

    Client();
    ~Client();

    void client_communicate_with_server();
    void client_init_connection(Socket socket);
    void client_set_message_length(int len);
    void client_set_message(char* msg);
    char* client_get_message();
    int client_get_message_length();
};

#endif
