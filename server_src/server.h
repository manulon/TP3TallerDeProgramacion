#ifndef SERVER_H
#define SERVER_H

#include "../common_src/Socket.h"

class Server{
private:
    const char*  servicename;
    char* message_read;
    short int message_read_length;

    bool _server_init_connection(Socket socket,Socket peer);

public:
    Server(char* const* argv);
    ~Server();

    bool server_init_connection(Socket socket,Socket peer);
    void server_communicate_with_client();
};

#endif
