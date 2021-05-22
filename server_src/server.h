#ifndef SERVER_H
#define SERVER_H

#include "../common_src/Socket.h"
#include "serverProtocol.h"
#include <string>

class Server{
private:
    const char*  servicename;
    std::string message_read;
    Socket socket;
    Socket peer;
    Server_Protocol protocol;

    bool start_connection(Socket& socket,Socket& peer);

public:
    Server(char const* argv[]);
    ~Server();

    void communicate_with_client();
};

#endif
