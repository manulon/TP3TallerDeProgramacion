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

    void communicate_with_server();
    void init_connection(Socket socket);
    void set_message_length(int len);
    void set_message(char* msg);
    char* get_message();
    int get_message_length();
};

#endif
