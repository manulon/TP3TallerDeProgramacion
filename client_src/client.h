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
    explicit Client(char const *argv[]);
    ~Client();

    //Comienza la comunicacion con el servidor.
    //Pre: Ya hay una conexion establecida.
    void communicate_with_server();
};

#endif
