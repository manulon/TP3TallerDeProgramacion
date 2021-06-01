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

    //Inicia el protocolo de comunicacion por parte del cliente
    //y comienza la comunicacion con el servidor.
    //Pre: Ya hay una conexion establecida.
    void communicate_with_server();

    //El socket del cliente se conecta a los puertos
    //requeridos.
    //Pre: Los puertos son validos.
    //Post: Se establece una conexion.
    void init_connection();
};

#endif
