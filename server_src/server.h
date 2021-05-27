#ifndef SERVER_H
#define SERVER_H

#include "../common_src/Socket.h"
#include "ThreadAcceptor.h"
#include "serverGameContainer.h"
#include <string>

class Server{
private:
    const char*  servicename;
    std::string message_read;
    Socket socket;
    GameContainer games;
    ThreadAcceptor* acceptor;

    

public:
    Server(char const* argv[]);
    ~Server();

    void start();
    bool start_connection();
};

#endif
