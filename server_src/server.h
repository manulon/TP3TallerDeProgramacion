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
    explicit Server(char const* argv[]);
    ~Server();

    //Crea un nuevo Thread Acceptor y lo ejecuta.
    void start();
    
    //Comienza a escuchar conexiones.
    bool start_connection();
    
    //Deja de aceptar conexiones, cerrando el socket, frenando 
    //el Thread Acceptor y joinenandolo.
    void stop_accepting();
};

#endif
