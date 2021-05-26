#include "serverProtocol.h"
#include "../common_src/TaTeTi.h"
#include "../common_src/GameFinishedException.h"

#include <iostream>
#include <vector>

Server_Protocol:: Server_Protocol():token(){}

void Server_Protocol:: init(const Socket& socket){
   this->socket = socket;
}

void Server_Protocol:: start_communication_protocol(){
    this->comm.init(std::move(this->socket));

    select_execution_mode();
}

void Server_Protocol:: set_token(const char& token){
    this->token = token;
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
    set_token(HOST_TOKEN);
    int bytes_received(0);
    
    uint16_t game_name_size(0);
    game_name_size = this->comm.receive_size(&game_name_size);
    
    std::vector<char> message(game_name_size+1);
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

    if( bytes_received > 0){
        try{    
            makePlay(message.data());
            check_game_status();
            send_board();
        } catch( GameFinishedException &error ){
            send_board_with_message();
        }
    }
}

void Server_Protocol:: check_game_status(){
    this->game.checkGameStatus();
}

void Server_Protocol:: send_board(){
    std::string board("");
    board = this->game.get_board();

    this->comm.send_size((int)board.length());
    this->comm.send_message(board.c_str(),board.length());
}

void Server_Protocol:: send_board_with_message(){
    std::string board("");
    board = this->game.get_board();
    board += "\nFelicitaciones! Ganaste! \n";

    this->comm.send_size((int)board.length());
    this->comm.send_message(board.c_str(),board.length());
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

    this->game.setNewPosition(this->token,column,row);
}

Server_Protocol:: ~Server_Protocol(){}

