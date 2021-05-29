#include "server.h"
#include <stdio.h>
#include <iostream>
Server:: Server(char const* argv[]):
servicename(argv[1]),acceptor(){}

Server:: ~Server(){
    this->acceptor->stop();
    delete this->acceptor;
}

void Server:: start(){
    this->acceptor = new ThreadAcceptor(this->socket,&(this->games));
    this->acceptor->start();
}

bool Server:: start_connection(){
    return this->socket.bind_and_listen(NULL, this->servicename);
}

void Server:: stop_accepting(){
    this->socket.socket_close();
    this->acceptor->join();
}
