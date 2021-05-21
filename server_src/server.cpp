#include "server.h"
#include <stdio.h>

Server:: Server(char* const* argv){
    this->servicename = argv[1];
}

Server:: ~Server(){}

bool Server:: server_init_connection(Socket socket,Socket peer){
    bool bind_and_listen_ok = false;

    bind_and_listen_ok =
        socket.socket_bind_and_listen(NULL, this->servicename);
    socket.socket_accept(peer);

    return bind_and_listen_ok;
}

void Server:: server_communicate_with_client(){
    Socket socket;
	Socket peer;

    //server_protocol_init(&protocol,&peer,self);

    if ( server_init_connection(socket,peer) )
        //server_protocol_start(&protocol,&socket,&encryptor);
        printf("hola");
    
}
