#include "server.h"
#include <stdio.h>
#include <iostream>
Server:: Server(char const* argv[]):
servicename(argv[1]){}

Server:: ~Server(){}

bool Server:: start_connection(Socket& socket,Socket& peer){
    bool bind_and_listen_ok = false;

    bind_and_listen_ok =
        peer.bind_and_listen(NULL, this->servicename);
    peer.socket_accept(socket);

    return bind_and_listen_ok;
}

void Server:: communicate_with_client(){
    if ( start_connection(this->socket,this->peer) ){
        this->protocol.init(std::move(this->socket));
        this->protocol.start_communication_protocol();       
    }    
}
