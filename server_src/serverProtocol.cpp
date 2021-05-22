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
    size = receive_size();

    receive_message(size);
}

int Server_Protocol:: receive_size(){
    return comm.receive_size();
}   

void Server_Protocol:: receive_message(int size){
    char* message = (char*)calloc((size+2),sizeof(char));
    comm.receive_message(size,message);
    
    makePlay(message);
    free(message);
}

void Server_Protocol:: makePlay(const char* message){
    unsigned char aux = 15; //0x0F
    unsigned char aux2 = 48; //0x30

    int column = message[1] >> 4;
    
    int row = message[1] & aux;
    
    column = (column | aux2)-48;
    row = (row | aux2)-48;

    this->game.setNewPosition(88,column,row);
    this->game.printBoard();
}

Server_Protocol:: ~Server_Protocol(){}

