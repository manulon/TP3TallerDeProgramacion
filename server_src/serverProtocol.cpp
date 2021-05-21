#include "serverProtocol.h"
#include <iostream>

Server_Protocol:: Server_Protocol(){}

void Server_Protocol:: init(const Socket& socket){
   this->socket = socket;
}
    
    
void Server_Protocol:: start_communication_protocol(){
    this->comm.init(std::move(this->socket));
    
    int size = 0;
    size = comm.receive_size();
    char* mensaje = (char*)calloc((size+1),sizeof(char));
    comm.receive_message(size,mensaje);
    mensaje[size] = 0;
    free(mensaje);
}
    
    
    
Server_Protocol:: ~Server_Protocol(){}

