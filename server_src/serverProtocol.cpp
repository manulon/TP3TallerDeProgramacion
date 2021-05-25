#include "serverProtocol.h"
#include "../common_src/TaTeTi.h"
#include "../common_src/GameFinishedException.h"

#include <iostream>
#include <vector>

Server_Protocol:: Server_Protocol(){}

void Server_Protocol:: init(const Socket& socket){
   this->socket = socket;
}

void Server_Protocol:: start_communication_protocol(){
    this->comm.init(std::move(this->socket));

    select_execution_mode();

    /*TaTeTi tateti("Partida 1");
    tateti.printBoard(); 
    
    int size = 0;
    size = receive_message(1);
    size = receive_message(size);
    while( size != 0){
        size = receive_message(1);
        size = receive_message(size);*/
    //}
}

void Server_Protocol:: select_execution_mode(){
    int bytes_received = 0;
    std::vector<char> mode(2);
    
    bytes_received = get_execution_mode(mode.data());

    while (bytes_received > 0){
        if ( strcmp(mode.data(),"n") == 0){
            receive_game_name();
        }else if ( strcmp(mode.data(),"listar") == 0){
        }else if ( strcmp(mode.data(),"unirse") == 0){
        }else if ( strcmp(mode.data(),"p") == 0){
            receive_play();
        }
        bytes_received = get_execution_mode(mode.data());
    }
}

void Server_Protocol:: receive_game_name(){
    int bytes_received = 0;
    
    int game_name_size = 0;
    game_name_size = this->comm.receive_size();
    
    std::vector<char> message(game_name_size);
    bytes_received = comm.receive_message(game_name_size,message.data());

    if( bytes_received > 0){
        this->gc.create_new_game(message.data());
    }
}

void Server_Protocol::receive_play(){
    int bytes_received = 0;
    std::vector<char> message(2);
    bytes_received = comm.receive_message(1,message.data());

    if( bytes_received > 0){
        try{    
            makePlay(message.data());
        } catch( GameFinishedException &error ){}
    }
}

int Server_Protocol::get_execution_mode(char* mode){
    int bytes_received = 0;
    bytes_received = comm.receive_message(1,mode);
    return bytes_received;
}

void Server_Protocol:: makePlay(const char* message){
    unsigned char aux = 15; //0x0F
    unsigned char aux2 = 48; //0x30

    int column = message[0] >> 4;
    
    int row = message[0] & aux;
    
    column = (column | aux2)-48;
    row = (row | aux2)-48;

    this->game.setNewPosition(88,column,row);
    this->game.printBoard();
    this->game.checkGameStatus();
}

Server_Protocol:: ~Server_Protocol(){}

