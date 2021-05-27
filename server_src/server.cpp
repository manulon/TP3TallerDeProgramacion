#include "server.h"
#include <stdio.h>
#include <iostream>
Server:: Server(char const* argv[]):
servicename(argv[1]){}

Server:: ~Server(){
    this->acceptor->stop();
    this->acceptor->join();
    delete this->acceptor;
}

void Server:: start(){
    this->acceptor = new ThreadAcceptor(this->socket,this->protocol);
    this->acceptor->start();
}

bool Server:: start_connection(){
    return this->socket.bind_and_listen(NULL, this->servicename);
}

