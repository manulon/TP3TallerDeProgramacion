#include "client.h"
#include <utility>

Client:: Client(char const *argv[]):
hostname(argv[1]),servicename(argv[2]),protocol(&this->socket){
    this->socket.socket_connect(this->hostname,this->servicename);
}

void Client:: communicate_with_server(){
    this->protocol.start_communication_protocol();
}

Client:: ~Client(){}
