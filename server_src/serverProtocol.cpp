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
}

void Server_Protocol:: select_execution_mode(){
    int bytes_received = 0;
    std::vector<char> mode(2);
    
    bytes_received = get_execution_mode(mode.data());

    while (bytes_received > 0){
        if ( strcmp(mode.data(),CREAR_KEY) == 0){
            receive_game_name();
        }else if ( strcmp(mode.data(),LISTAR_KEY) == 0){
            receive_list_command();
        }else if ( strcmp(mode.data(),"unirse") == 0){
        }else if ( strcmp(mode.data(),JUGAR_KEY) == 0){
            receive_play();
        }
        bytes_received = get_execution_mode(mode.data());
    }
}

void Server_Protocol:: receive_game_name(){
    int bytes_received(0);
    
    uint16_t game_name_size(0);
    game_name_size = this->comm.receive_size(&game_name_size);
    
    std::cout << game_name_size << std::endl;

    std::vector<char> message(game_name_size);
    bytes_received = comm.receive_message(game_name_size,message.data());

    if( bytes_received > 0)
        this->gc.create_new_game(message.data());
    
}

void Server_Protocol:: receive_list_command(){
    std::string all_games_name("");
    all_games_name = this->gc.get_all_values();
    
    this->comm.send_size((int)all_games_name.length());
    this->comm.send_message(all_games_name.c_str(),all_games_name.length());
}

void Server_Protocol::receive_play(){
    int bytes_received = 0;
    std::vector<char> message(2);
    bytes_received = comm.receive_message(1,message.data());

    std::string board("");
    if( bytes_received > 0){
        try{    
            makePlay(message.data());
            board = this->game.get_board();

            std::cout << (int)board.length() << std::endl;;

            this->comm.send_size((int)board.length());
            this->comm.send_message(board.c_str(),board.length());
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
    //this->game.printBoard();
    this->game.checkGameStatus();
}

Server_Protocol:: ~Server_Protocol(){}

