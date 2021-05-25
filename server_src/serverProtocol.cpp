#include "serverProtocol.h"
#include "../common_src/TaTeTi.h"
#include "../common_src/GameFinishedException.h"

#include <iostream>

Server_Protocol:: Server_Protocol(){}

void Server_Protocol:: init(const Socket& socket){
   this->socket = socket;
}

void Server_Protocol:: start_communication_protocol(){
    TaTeTi tateti("Partida 1");
    tateti.printBoard();
    
    this->comm.init(std::move(this->socket));
    
    int size = 0;
    size = receive_message(2);
    while( size != 0){
        size = receive_message(2);
    }
}

int Server_Protocol:: receive_message(const int& size){
    int bytes_received = 0;

    char* message = (char*)calloc((size+2),sizeof(char));
    bytes_received = comm.receive_message(size,message);
    
    if( bytes_received > 0){
        try{    
            makePlay(message);
        } catch( GameFinishedException &error ){}
    }
    
    free(message);

    return bytes_received;

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
    this->game.checkGameStatus();
}

Server_Protocol:: ~Server_Protocol(){}

