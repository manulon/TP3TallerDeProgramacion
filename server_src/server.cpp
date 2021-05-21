#include "server.h"
#include <stdio.h>
#include <iostream>
Server:: Server(char const* argv[]){
    this->servicename = argv[1];
}

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
        CommunicationProtocol commu(std::move(this->socket));
        //this->protocol.init(std::move(this->socket));
        int size = 0;
        size = commu.receive_size();
        char* mensaje = (char*)calloc((size+1),sizeof(char));
        commu.receive_message(size,mensaje);
        mensaje[size] = 0;
        free(mensaje);
    }    
}
