#include "serverProtocol.h"

/*Solo pa este caso */
#include "../common_src/TaTeTi.h"

#include <iostream>

Server_Protocol:: Server_Protocol(){}

void Server_Protocol:: init(const Socket& socket){
   this->socket = socket;
}

void Server_Protocol:: start_communication_protocol(){
    /*solo pa este caso*/
    TaTeTi tateti("Partida 1");
    tateti.printBoard();
    
    this->comm.init(std::move(this->socket));
    int size = 0;
    size = comm.receive_size();
    char* mensaje = (char*)calloc((size+1),sizeof(char));
    comm.receive_message(size,mensaje);
    
    unsigned char aux = 15; //0x0F
    unsigned char aux2 = 48; //0x30

    unsigned char column = mensaje[1] >> 4;
    
    unsigned char row = mensaje[1] & aux;
    
    mensaje[1] = column | aux2;
    mensaje[2] = row | aux2;

    mensaje[size] = 0;

    free(mensaje);
}
    
    
    
Server_Protocol:: ~Server_Protocol(){}

