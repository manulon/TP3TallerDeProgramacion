#ifndef SERVER_H
#define SERVER_H

#include "../common_src/Socket.h"
#include "serverProtocol.h"
#include "ThreadAcceptor.h"
#include <string>

class Server{
private:
    const char*  servicename;
    std::string message_read;
    Socket socket;
    Server_Protocol protocol;
    ThreadAcceptor* acceptor;

    

public:
    Server(char const* argv[]);
    ~Server();

    void start();
    bool start_connection();
};

#endif
