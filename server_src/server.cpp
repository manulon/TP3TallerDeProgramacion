#include "server.h"
#include <stdio.h>
#include <iostream>
Server:: Server(char const* argv[]):
servicename(argv[1]),acceptor(){}

Server:: ~Server(){
    this->acceptor->stop_clients();
    delete this->acceptor;
}

void Server:: start(){
    //try del aceptador que no encuentra una conexion en el bind and lisen
    this->acceptor = new ThreadAcceptor(&(this->games),this->servicename);
    this->acceptor->start();
}

void Server:: stop_accepting(){
    this->acceptor->close_socket();
    this->acceptor->stop();
    this->acceptor->join();
}
